/**
 *	@file	framebuffer_inl.hpp
 *
 *	@brief	Framebuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/framebuffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/image_view.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/texture.hpp>
#include <bksge/core/render/vulkan/detail/depth_stencil_buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
Framebuffer::Framebuffer(
	vulkan::DeviceSharedPtr const& device,
	vulkan::TextureSharedPtr const& color_buffer,
	vulkan::DepthStencilBufferSharedPtr const& depth_stencil_buffer,
	vulkan::RenderPassSharedPtr const& render_pass)
	: m_device(device)
	, m_framebuffer(VK_NULL_HANDLE)
	, m_color_buffer(color_buffer)
	, m_depth_stencil_buffer(depth_stencil_buffer)
	, m_render_pass(render_pass)
{
	m_extent = color_buffer->image()->extent();
	bksge::vector<::VkImageView> attachments;
	attachments.push_back(*color_buffer->image_view());
	if (depth_stencil_buffer)
	{
		attachments.push_back(*depth_stencil_buffer->image_view());
	}

	vk::FramebufferCreateInfo info;
	info.renderPass      = *render_pass;
	info.layers          = 1;
	info.SetAttachments(attachments);
	info.SetExtent(m_extent);

	vk::CreateFramebuffer(*m_device, &info, nullptr, &m_framebuffer);
}

BKSGE_INLINE
Framebuffer::~Framebuffer()
{
	vk::DestroyFramebuffer(*m_device, m_framebuffer, nullptr);
}

BKSGE_INLINE void
Framebuffer::Clear(
	vulkan::CommandBuffer* command_buffer,
	bksge::ClearState const& clear_state)
{
	::VkImageAspectFlags color_aspect_mask = 0;
	::VkImageAspectFlags depth_aspect_mask = 0;
	if (Test(clear_state.flag(), bksge::ClearFlag::kColor))
	{
		color_aspect_mask |= VK_IMAGE_ASPECT_COLOR_BIT;
	}
	if (Test(clear_state.flag(), bksge::ClearFlag::kDepth))
	{
		depth_aspect_mask |= VK_IMAGE_ASPECT_DEPTH_BIT;
	}
	if (Test(clear_state.flag(), bksge::ClearFlag::kStencil))
	{
		depth_aspect_mask |= VK_IMAGE_ASPECT_STENCIL_BIT;
	}

	m_color_buffer->image()->ClearColor(
		command_buffer,
		color_aspect_mask,
		clear_state.color());

	if (m_depth_stencil_buffer)
	{
		m_depth_stencil_buffer->image()->ClearDepthStencil(
			command_buffer,
			depth_aspect_mask,
			clear_state.depth(),
			clear_state.stencil());
	}
}

BKSGE_INLINE ::VkExtent2D const&
Framebuffer::extent(void) const
{
	return m_extent;
}

BKSGE_INLINE vulkan::TextureSharedPtr const&
Framebuffer::color_buffer(void) const
{
	return m_color_buffer;
}

BKSGE_INLINE vulkan::RenderPassSharedPtr const&
Framebuffer::render_pass(void) const
{
	return m_render_pass;
}

BKSGE_INLINE
Framebuffer::operator ::VkFramebuffer() const
{
	return m_framebuffer;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
