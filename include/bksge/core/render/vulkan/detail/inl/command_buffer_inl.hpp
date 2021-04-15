/**
 *	@file	command_buffer_inl.hpp
 *
 *	@brief	CommandBuffer クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/command_pool.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/framebuffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
CommandBuffer::CommandBuffer(
	vulkan::CommandPoolSharedPtr const& command_pool)
	: m_command_pool(command_pool)
	, m_command_buffer(VK_NULL_HANDLE)
{
	m_command_buffer =
		m_command_pool->AllocateCommandBuffer(
			VK_COMMAND_BUFFER_LEVEL_PRIMARY);
}

BKSGE_INLINE
CommandBuffer::~CommandBuffer()
{
	m_command_pool->FreeCommandBuffer(m_command_buffer);
}

BKSGE_INLINE
CommandBuffer::operator ::VkCommandBuffer() const
{
	return m_command_buffer;
}

BKSGE_INLINE ::VkCommandBuffer const*
CommandBuffer::GetAddressOf(void) const
{
	return &m_command_buffer;
}

BKSGE_INLINE void
CommandBuffer::Begin(::VkCommandBufferUsageFlags flags)
{
	vk::CommandBufferBeginInfo begin_info;
	begin_info.flags = flags;

	vk::BeginCommandBuffer(m_command_buffer, &begin_info);
}

BKSGE_INLINE void
CommandBuffer::End(void)
{
	vk::EndCommandBuffer(m_command_buffer);
}

BKSGE_INLINE void
CommandBuffer::BeginRenderPass(
	vulkan::RenderPass const& render_pass,
	vulkan::Framebuffer const& framebuffer)
{
	vk::RenderPassBeginInfo render_pass_begin;
	render_pass_begin.renderPass          = render_pass;
	render_pass_begin.framebuffer         = framebuffer;
	render_pass_begin.renderArea.offset.x = 0;
	render_pass_begin.renderArea.offset.y = 0;
	render_pass_begin.renderArea.extent   = framebuffer.extent();

	vk::CmdBeginRenderPass(
		m_command_buffer,
		&render_pass_begin,
		VK_SUBPASS_CONTENTS_INLINE);
}

BKSGE_INLINE void
CommandBuffer::EndRenderPass(void)
{
	vk::CmdEndRenderPass(m_command_buffer);
}

BKSGE_INLINE void
CommandBuffer::SetViewport(::VkViewport const& viewport)
{
	vk::CmdSetViewport(m_command_buffer, 0, 1, &viewport);
}

BKSGE_INLINE void
CommandBuffer::SetScissor(::VkRect2D const& scissor_rect)
{
	vk::CmdSetScissor(m_command_buffer, 0, 1, &scissor_rect);
}

BKSGE_INLINE void
CommandBuffer::BindPipeline(
	::VkPipelineBindPoint pipeline_bind_point,
	::VkPipeline          pipeline)
{
	vk::CmdBindPipeline(
		m_command_buffer,
		pipeline_bind_point,
		pipeline);
}

BKSGE_INLINE void
CommandBuffer::PushDescriptorSet(
	::VkDevice                                 device,
	::VkPipelineBindPoint                      pipeline_bind_point,
	::VkPipelineLayout                         layout,
	bksge::uint32_t                            set,
	bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes)
{
	if (!descriptor_writes.empty())
	{
		vk::CmdPushDescriptorSetKHR(
			device,
			m_command_buffer,
			pipeline_bind_point,
			layout,
			set,
			static_cast<bksge::uint32_t>(descriptor_writes.size()),
			descriptor_writes.data());
	}
}

BKSGE_INLINE bksge::unique_ptr<vulkan::CommandBuffer>
BeginSingleTimeCommands(
	vulkan::CommandPoolSharedPtr const& command_pool)
{
	auto command_buffer = bksge::make_unique<vulkan::CommandBuffer>(command_pool);

	command_buffer->Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

	return command_buffer;
}

BKSGE_INLINE void
EndSingleTimeCommands(
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::unique_ptr<vulkan::CommandBuffer> const& command_buffer)
{
	command_buffer->End();

	vk::SubmitInfo submit_info;
	submit_info.SetCommandBuffers(command_buffer->GetAddressOf());

	auto graphics_queue = command_pool->GetQueue();
	vk::QueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
	vk::QueueWaitIdle(graphics_queue);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP
