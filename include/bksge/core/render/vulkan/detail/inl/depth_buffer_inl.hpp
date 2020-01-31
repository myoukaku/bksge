/**
 *	@file	depth_buffer_inl.hpp
 *
 *	@brief	DepthBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/depth_buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/physical_device.hpp>
#include <bksge/core/render/vulkan/detail/image_object.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
DepthBuffer::DepthBuffer(
	vulkan::DeviceSharedPtr const& device,
	::VkExtent2D const& extent,
	::VkSampleCountFlagBits num_samples)
{
	::VkFormat format = VK_FORMAT_UNDEFINED;

	auto physical_device = device->GetPhysicalDevice();

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
		num_samples,
		tiling,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	::VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (format == VK_FORMAT_D16_UNORM_S8_UINT ||
		format == VK_FORMAT_D24_UNORM_S8_UINT ||
		format == VK_FORMAT_D32_SFLOAT_S8_UINT)
	{
		aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	m_image_view = bksge::make_unique<vulkan::ImageView>(
		device,
		m_image->GetImage(),
		format,
		aspectMask);
}

BKSGE_INLINE
DepthBuffer::~DepthBuffer()
{
}

BKSGE_INLINE ::VkFormat const&
DepthBuffer::GetFormat(void) const
{
	return m_image->GetFormat();
}

BKSGE_INLINE vulkan::ImageView const&
DepthBuffer::GetImageView(void) const
{
	return *m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_BUFFER_INL_HPP
