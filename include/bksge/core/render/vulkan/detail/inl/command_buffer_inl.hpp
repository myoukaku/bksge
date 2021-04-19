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
	: m_command_buffer(VK_NULL_HANDLE)
	, m_command_pool(command_pool)
	, m_device(command_pool->device())
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
CommandBuffer::BindIndexBuffer(
	::VkBuffer     buffer,
	::VkDeviceSize offset,
	::VkIndexType  index_type)
{
	vk::CmdBindIndexBuffer(m_command_buffer, buffer, offset, index_type);
}

BKSGE_INLINE void
CommandBuffer::BindVertexBuffers(
	bksge::uint32_t       first_binding,
	bksge::uint32_t       binding_count,
	::VkBuffer const*     buffers,
	::VkDeviceSize const* offsets)
{
	vk::CmdBindVertexBuffers(
		m_command_buffer,
		first_binding,
		binding_count,
		buffers,
		offsets);
}

BKSGE_INLINE void
CommandBuffer::Draw(
	bksge::uint32_t	vertex_count,
	bksge::uint32_t	instance_count,
	bksge::uint32_t	first_vertex,
	bksge::uint32_t	first_instance)
{
	vk::CmdDraw(
		m_command_buffer,
		vertex_count,
		instance_count,
		first_vertex,
		first_instance);
}

BKSGE_INLINE void
CommandBuffer::DrawIndexed(
	bksge::uint32_t index_count,
	bksge::uint32_t instance_count,
	bksge::uint32_t first_index,
	bksge::int32_t  vertex_offset,
	bksge::uint32_t first_instance)
{
	vk::CmdDrawIndexed(
		m_command_buffer,
		index_count,
		instance_count,
		first_index,
		vertex_offset,
		first_instance);
}

BKSGE_INLINE void
CommandBuffer::CopyBufferToImage(
	::VkBuffer                 src_buffer,
	::VkImage                  dst_image,
	::VkImageLayout            dst_image_layout,
	bksge::uint32_t            region_count,
	::VkBufferImageCopy const* regions)
{
	vk::CmdCopyBufferToImage(
		m_command_buffer,
		src_buffer,
		dst_image,
		dst_image_layout,
		region_count,
		regions);
}

BKSGE_INLINE void
CommandBuffer::ClearColorImage(
	::VkImage                        image,
	::VkImageLayout                  image_layout,
	::VkClearColorValue const*       color,
	bksge::uint32_t                  range_count,
	::VkImageSubresourceRange const* ranges)
{
	vk::CmdClearColorImage(
		m_command_buffer,
		image,
		image_layout,
		color,
		range_count,
		ranges);
}

BKSGE_INLINE void
CommandBuffer::ClearDepthStencilImage(
	::VkImage                         image,
	::VkImageLayout                   image_layout,
	::VkClearDepthStencilValue const* depth_stencil,
	bksge::uint32_t                   range_count,
	::VkImageSubresourceRange const*  ranges)
{
	vk::CmdClearDepthStencilImage(
		m_command_buffer,
		image,
		image_layout,
		depth_stencil,
		range_count,
		ranges);
}

BKSGE_INLINE void
CommandBuffer::PipelineBarrier(
	::VkPipelineStageFlags         src_stage_mask,
	::VkPipelineStageFlags         dst_stage_mask,
	::VkDependencyFlags            dependency_flags,
	bksge::uint32_t                memory_barrier_count,
	::VkMemoryBarrier const*       memory_barriers,
	bksge::uint32_t                buffer_memory_barrier_count,
	::VkBufferMemoryBarrier const* buffer_memory_barriers,
	bksge::uint32_t                image_memory_barrier_count,
	::VkImageMemoryBarrier const*  image_memory_barriers)
{
	vk::CmdPipelineBarrier(
		m_command_buffer,
		src_stage_mask,
		dst_stage_mask,
		dependency_flags,
		memory_barrier_count,
		memory_barriers,
		buffer_memory_barrier_count,
		buffer_memory_barriers,
		image_memory_barrier_count,
		image_memory_barriers);
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
CommandBuffer::PushDescriptorSet(
	::VkPipelineBindPoint                      pipeline_bind_point,
	::VkPipelineLayout                         layout,
	bksge::uint32_t                            set,
	bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes)
{
	m_device->PushDescriptorSet(
		m_command_buffer,
		pipeline_bind_point,
		layout,
		set,
		descriptor_writes);
}

BKSGE_INLINE ::VkCommandBuffer const*
CommandBuffer::GetAddressOf(void) const
{
	return &m_command_buffer;
}

BKSGE_INLINE ::VkQueue
CommandBuffer::GetQueue(void) const
{
	return m_command_pool->GetQueue();
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
	bksge::unique_ptr<vulkan::CommandBuffer> const& command_buffer)
{
	command_buffer->End();

	vk::SubmitInfo submit_info;
	submit_info.SetCommandBuffers(command_buffer->GetAddressOf());

	auto graphics_queue = command_buffer->GetQueue();
	vk::QueueSubmit(graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
	vk::QueueWaitIdle(graphics_queue);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_COMMAND_BUFFER_INL_HPP
