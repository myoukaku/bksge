/**
 *	@file	render_texture_inl.hpp
 *
 *	@brief	RenderTexture クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_TEXTURE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_TEXTURE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/render_texture.hpp>
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
RenderTexture::RenderTexture(
	vulkan::DeviceSharedPtr const& device,
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkFormat format,
	::VkExtent2D const& extent,
	::VkSampleCountFlagBits num_samples)
{
	auto physical_device = device->physical_device();

	::VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
	auto const props = physical_device->GetFormatProperties(format);
	if (props.linearTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
	{
		tiling = VK_IMAGE_TILING_LINEAR;
	}
	else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT)
	{
		tiling = VK_IMAGE_TILING_OPTIMAL;
	}
	else
	{
		// TODO エラー処理
	}

	bksge::uint32_t const mipmap_count = 1;

	::VkImageUsageFlags const usage =
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_SAMPLED_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	m_image = bksge::make_unique<vulkan::ImageObject>(
		device,
		format,
		extent,
		mipmap_count,
		num_samples,
		tiling,
		usage,
		VK_IMAGE_LAYOUT_UNDEFINED,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	::VkImageAspectFlags const aspect = VK_IMAGE_ASPECT_COLOR_BIT;

	m_image_view = bksge::make_unique<vulkan::ImageView>(
		device,
		m_image->image(),
		aspect);

	this->TransitionLayout(
		command_pool,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
}

BKSGE_INLINE
RenderTexture::~RenderTexture()
{
}

BKSGE_INLINE void
RenderTexture::TransitionLayout(
	vulkan::CommandPoolSharedPtr const& command_pool,
	::VkImageLayout new_layout)
{
	m_image->TransitionLayout(
		command_pool,
		m_image_view->aspect_mask(),
		new_layout);
}

BKSGE_INLINE void
RenderTexture::Clear(
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::ClearState const& clear_state)
{
	::VkImageAspectFlags aspect_mask = 0;
	if (Test(clear_state.flag(), bksge::ClearFlag::kColor))
	{
		aspect_mask |= VK_IMAGE_ASPECT_COLOR_BIT;
	}

	if (aspect_mask == 0)
	{
		return;
	}

	this->TransitionLayout(
		command_pool,
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	::VkClearColorValue clear_value;
	clear_value.float32[0] = clear_state.color().r();
	clear_value.float32[1] = clear_state.color().g();
	clear_value.float32[2] = clear_state.color().b();
	clear_value.float32[3] = clear_state.color().a();

	::VkImageSubresourceRange range;
	range.aspectMask     = aspect_mask;
	range.baseMipLevel   = 0;
	range.levelCount     = 1;
	range.baseArrayLayer = 0;
	range.layerCount     = 1;

	auto command_buffer = BeginSingleTimeCommands(command_pool);
	vk::CmdClearColorImage(
		*command_buffer,
		m_image->image(),
		VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
		&clear_value,
		1, &range);
	EndSingleTimeCommands(command_pool, command_buffer);

	this->TransitionLayout(
		command_pool,
		VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
}

BKSGE_INLINE vulkan::Image const&
RenderTexture::image(void) const
{
	return m_image->image();
}

BKSGE_INLINE vulkan::ImageView const&
RenderTexture::image_view(void) const
{
	return *m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_RENDER_TEXTURE_INL_HPP
