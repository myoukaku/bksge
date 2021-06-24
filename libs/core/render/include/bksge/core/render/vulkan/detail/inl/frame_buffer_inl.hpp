/**
 *	@file	frame_buffer_inl.hpp
 *
 *	@brief	FrameBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAME_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAME_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/frame_buffer.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/image.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
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
FrameBuffer::FrameBuffer(
	vulkan::DeviceSharedPtr const& device,
	vulkan::Extent2D const& extent,
	::VkSampleCountFlagBits num_samples,
	vulkan::ImageSharedPtr const& color_buffer,
	vulkan::ImageSharedPtr const& depth_stencil_buffer)
	: m_frame_buffer(VK_NULL_HANDLE)
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
		depth_stencil_buffer ? depth_stencil_buffer.get() : nullptr);

	bksge::vector<::VkImageView> attachments;
	if (color_buffer)
	{
		attachments.push_back(color_buffer->image_view());
	}
	if (depth_stencil_buffer)
	{
		attachments.push_back(depth_stencil_buffer->image_view());
	}

	vk::FramebufferCreateInfo info;
	info.renderPass = *m_render_pass;
	info.layers     = 1;
	info.SetAttachments(attachments);
	info.SetExtent(m_extent);

	m_frame_buffer = m_device->CreateFramebuffer(info);
}

BKSGE_INLINE
FrameBuffer::~FrameBuffer()
{
	m_device->DestroyFramebuffer(m_frame_buffer);
}

BKSGE_INLINE void
FrameBuffer::Clear(
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
		m_depth_stencil_buffer->ClearDepthStencil(
			command_buffer,
			depth_aspect_mask,
			clear_state.depth(),
			clear_state.stencil());
	}
}

BKSGE_INLINE vk::RenderPassBeginInfo
FrameBuffer::GetRenderPassBeginInfo(void) const
{
	vk::RenderPassBeginInfo render_pass_begin;
	render_pass_begin.renderPass          = *m_render_pass;
	render_pass_begin.framebuffer         = m_frame_buffer;
	render_pass_begin.renderArea.offset.x = 0;
	render_pass_begin.renderArea.offset.y = 0;
	render_pass_begin.renderArea.extent   = m_extent;
	return render_pass_begin;
}

BKSGE_INLINE vulkan::ImageSharedPtr const&
FrameBuffer::color_buffer(void) const
{
	return m_color_buffer;
}

BKSGE_INLINE vulkan::RenderPassSharedPtr const&
FrameBuffer::render_pass(void) const
{
	return m_render_pass;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_FRAME_BUFFER_INL_HPP
