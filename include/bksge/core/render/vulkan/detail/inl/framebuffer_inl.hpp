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
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/texture.hpp>
#include <bksge/core/render/vulkan/detail/depth_stencil_buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/clear_state.hpp>
#include <bksge/fnd/memory/make_shared.hpp>
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
	vulkan::Extent2D const& extent,
	::VkSampleCountFlagBits num_samples,
	vulkan::ImageSharedPtr const& color_buffer,
	vulkan::DepthStencilBufferSharedPtr const& depth_stencil_buffer)
	: m_framebuffer(VK_NULL_HANDLE)
	, m_device(device)
	, m_extent(extent)
	, m_color_buffer(color_buffer)
	, m_depth_stencil_buffer(depth_stencil_buffer)
	, m_render_pass()
{
	m_render_pass = bksge::make_shared<vulkan::RenderPass>(
		device,
		num_samples,
		color_buffer ? color_buffer.get() : nullptr,
		depth_stencil_buffer ? depth_stencil_buffer->image().get() : nullptr);

	bksge::vector<::VkImageView> attachments;
	attachments.push_back(color_buffer->image_view());
	if (depth_stencil_buffer)
	{
		attachments.push_back(depth_stencil_buffer->image()->image_view());
	}

	vk::FramebufferCreateInfo info;
	info.renderPass = *m_render_pass;
	info.layers     = 1;
	info.SetAttachments(attachments);
	info.SetExtent(m_extent);

	m_framebuffer = m_device->CreateFramebuffer(info);
}

BKSGE_INLINE
Framebuffer::~Framebuffer()
{
	m_device->DestroyFramebuffer(m_framebuffer);
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

	m_color_buffer->ClearColor(
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

BKSGE_INLINE vk::RenderPassBeginInfo
Framebuffer::GetRenderPassBeginInfo(void) const
{
	vk::RenderPassBeginInfo render_pass_begin;
	render_pass_begin.renderPass          = *m_render_pass;
	render_pass_begin.framebuffer         = m_framebuffer;
	render_pass_begin.renderArea.offset.x = 0;
	render_pass_begin.renderArea.offset.y = 0;
	render_pass_begin.renderArea.extent   = m_extent;
	return render_pass_begin;
}

BKSGE_INLINE vulkan::ImageSharedPtr const&
Framebuffer::color_buffer(void) const
{
	return m_color_buffer;
}

BKSGE_INLINE vulkan::RenderPassSharedPtr const&
Framebuffer::render_pass(void) const
{
	return m_render_pass;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAMEBUFFER_INL_HPP
