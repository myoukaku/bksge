/**
 *	@file	command_buffer.hpp
 *
 *	@brief	CommandBuffer クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP

#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_pool_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/framebuffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class CommandBuffer
{
public:
	explicit CommandBuffer(
		vulkan::CommandPoolSharedPtr const& command_pool);

	~CommandBuffer();

	void Begin(::VkCommandBufferUsageFlags flags);
	void End(void);

	void BindPipeline(
		::VkPipelineBindPoint pipeline_bind_point,
		::VkPipeline          pipeline);

	void SetViewport(::VkViewport const& viewport);

	void SetScissor(::VkRect2D const& scissor_rect);

	void BindIndexBuffer(
		::VkBuffer     buffer,
		::VkDeviceSize offset,
		::VkIndexType  index_type);

	void BindVertexBuffers(
		bksge::uint32_t       first_binding,
		bksge::uint32_t       binding_count,
		::VkBuffer const*     buffers,
		::VkDeviceSize const* offsets);

	void Draw(
		bksge::uint32_t	vertex_count,
		bksge::uint32_t	instance_count,
		bksge::uint32_t	first_vertex,
		bksge::uint32_t	first_instance);

	void DrawIndexed(
		bksge::uint32_t index_count,
		bksge::uint32_t instance_count,
		bksge::uint32_t first_index,
		bksge::int32_t  vertex_offset,
		bksge::uint32_t first_instance);

	void CopyBufferToImage(
		::VkBuffer                 src_buffer,
		::VkImage                  dst_image,
		::VkImageLayout            dst_image_layout,
		bksge::uint32_t            region_count,
		::VkBufferImageCopy const* regions);

	void ClearColorImage(
		::VkImage                        image,
		::VkImageLayout                  image_layout,
		::VkClearColorValue const*       color,
		bksge::uint32_t                  range_count,
		::VkImageSubresourceRange const* ranges);

	void ClearDepthStencilImage(
		::VkImage                         image,
		::VkImageLayout                   image_layout,
		::VkClearDepthStencilValue const* depth_stencil,
		bksge::uint32_t                   range_count,
		::VkImageSubresourceRange const*  ranges);

	void PipelineBarrier(
		::VkPipelineStageFlags         src_stage_mask,
		::VkPipelineStageFlags         dst_stage_mask,
		::VkDependencyFlags            dependency_flags,
		bksge::uint32_t                memory_barrier_count,
		::VkMemoryBarrier const*       memory_barriers,
		bksge::uint32_t                buffer_memory_barrier_count,
		::VkBufferMemoryBarrier const* buffer_memory_barriers,
		bksge::uint32_t                image_memory_barrier_count,
		::VkImageMemoryBarrier const*  image_memory_barriers);

	void BeginRenderPass(
		vulkan::RenderPass const& render_pass,
		vulkan::Framebuffer const& framebuffer);
	void EndRenderPass(void);

	void PushDescriptorSet(
		::VkPipelineBindPoint                        pipeline_bind_point,
		::VkPipelineLayout                           layout,
		bksge::uint32_t                              set,
		bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes);

	::VkCommandBuffer const* GetAddressOf(void) const;

	::VkQueue	GetQueue(void) const;

private:
	// noncopyable
	CommandBuffer(CommandBuffer const&) = delete;
	CommandBuffer& operator=(CommandBuffer const&) = delete;

private:
	::VkCommandBuffer				m_command_buffer;
	vulkan::CommandPoolSharedPtr	m_command_pool;
	vulkan::DeviceSharedPtr			m_device;
};

bksge::unique_ptr<vulkan::CommandBuffer>
BeginSingleTimeCommands(
	vulkan::CommandPoolSharedPtr const& command_pool);

void
EndSingleTimeCommands(
	bksge::unique_ptr<vulkan::CommandBuffer> const& command_buffer);

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/command_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
