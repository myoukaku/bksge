/**
 *	@file	depth_stencil_buffer_inl.hpp
 *
 *	@brief	DepthStencilBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/depth_stencil_buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/image_object.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
DepthStencilBuffer::DepthStencilBuffer(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkExtent2D const& extent,
	::VkSampleCountFlagBits num_samples)
{
	::VkFormat format = VK_FORMAT_D24_UNORM_S8_UINT;//VK_FORMAT_UNDEFINED;

	auto physical_device = device->physical_device();

	::VkFormatProperties props;

	/* allow custom depth formats */
#if defined(__ANDROID__)
	// Depth format needs to be VK_FORMAT_D24_UNORM_S8_UINT on Android (if available).
	vk::GetPhysicalDeviceFormatProperties(info.gpus[0], VK_FORMAT_D24_UNORM_S8_UINT, &props);
	if ((props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT) ||
		(props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT))
	{
		format = VK_FORMAT_D24_UNORM_S8_UINT;
	}
	else
	{
		format = VK_FORMAT_D16_UNORM;
	}
#elif defined(VK_USE_PLATFORM_IOS_MVK)
	if (format == VK_FORMAT_UNDEFINED)
	{
		format = VK_FORMAT_D32_SFLOAT;
	}
#else
	if (format == VK_FORMAT_UNDEFINED)
	{
		format = VK_FORMAT_D16_UNORM;
	}
#endif

	::VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
	vk::GetPhysicalDeviceFormatProperties(*physical_device, format, &props);
	if (props.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
	{
		tiling = VK_IMAGE_TILING_LINEAR;
	}
	else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
	{
		tiling = VK_IMAGE_TILING_OPTIMAL;
	}
	else
	{
	 /* Try other depth formats? */
		//std::cout << "depth_format " << format << " Unsupported.\n";
		exit(-1);
	}

	m_image = bksge::make_unique<vulkan::ImageObject>(
		device,
		format,
		extent,
		1,
		num_samples,
		tiling,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	::VkImageAspectFlags aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (format == VK_FORMAT_D16_UNORM_S8_UINT ||
		format == VK_FORMAT_D24_UNORM_S8_UINT ||
		format == VK_FORMAT_D32_SFLOAT_S8_UINT)
	{
		aspect_mask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	m_image->TransitionLayout(
		command_pool,
		aspect_mask,
		1,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

	m_image_view = bksge::make_unique<vulkan::ImageView>(
		device,
		m_image->image(),
		format,
		aspect_mask,
		1);
}

BKSGE_INLINE
DepthStencilBuffer::~DepthStencilBuffer()
{
}

BKSGE_INLINE void
DepthStencilBuffer::Clear(
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::ClearState const& clear_state)
{
	::VkImageAspectFlags clear_mask = 0;
	if (Test(clear_state.flag(), bksge::ClearFlag::kDepth))
	{
		clear_mask |= VK_IMAGE_ASPECT_DEPTH_BIT;
	}
	if (Test(clear_state.flag(), bksge::ClearFlag::kStencil))
	{
		clear_mask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	if (clear_mask == 0)
	{
		return;
	}

	m_image->TransitionLayout(
		command_pool,
		VK_IMAGE_ASPECT_DEPTH_BIT |
		VK_IMAGE_ASPECT_STENCIL_BIT,
		1,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	::VkClearDepthStencilValue clear_value;
	clear_value.depth   = clear_state.depth();
	clear_value.stencil = clear_state.stencil();

	::VkImageSubresourceRange range;
	range.aspectMask     = clear_mask;
	range.baseMipLevel   = 0;
	range.levelCount     = 1;
	range.baseArrayLayer = 0;
	range.layerCount     = 1;

	auto command_buffer = BeginSingleTimeCommands(command_pool);
	vk::CmdClearDepthStencilImage(
		*command_buffer,
		m_image->image(),
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		&clear_value,
		1, &range);
	EndSingleTimeCommands(command_pool, command_buffer);

	m_image->TransitionLayout(
		command_pool,
		VK_IMAGE_ASPECT_DEPTH_BIT |
		VK_IMAGE_ASPECT_STENCIL_BIT,
		1,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

BKSGE_INLINE ::VkFormat const&
DepthStencilBuffer::format(void) const
{
	return m_image->image().format();
}

BKSGE_INLINE vulkan::ImageView const&
DepthStencilBuffer::image_view(void) const
{
	return *m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_BUFFER_INL_HPP
