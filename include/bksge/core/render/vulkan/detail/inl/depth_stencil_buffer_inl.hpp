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
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/extent2d.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_shared.hpp>

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
	::VkFormat format,
	vulkan::Extent2D const& extent,
	::VkSampleCountFlagBits num_samples)
{
	bksge::uint32_t const mipmap_count = 1;

	m_image = bksge::make_shared<vulkan::Image>(
		device,
		format,
		extent,
		mipmap_count,
		num_samples,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT |
		VK_IMAGE_USAGE_TRANSFER_DST_BIT);

	::VkImageAspectFlags aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT;
	if (format == VK_FORMAT_D16_UNORM_S8_UINT ||
		format == VK_FORMAT_D24_UNORM_S8_UINT ||
		format == VK_FORMAT_D32_SFLOAT_S8_UINT)
	{
		aspect_mask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	m_image_view = bksge::make_shared<vulkan::ImageView>(
		device,
		*m_image,
		aspect_mask);

	m_image->TransitionLayout(
		command_pool,
		aspect_mask,
		VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

BKSGE_INLINE
DepthStencilBuffer::~DepthStencilBuffer()
{
}

BKSGE_INLINE vulkan::ImageSharedPtr const&
DepthStencilBuffer::image(void) const
{
	return m_image;
}

BKSGE_INLINE vulkan::ImageViewSharedPtr const&
DepthStencilBuffer::image_view(void) const
{
	return m_image_view;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_BUFFER_INL_HPP
