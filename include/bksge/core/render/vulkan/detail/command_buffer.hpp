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

	void BeginRenderPass(
		vulkan::RenderPass const& render_pass,
		vulkan::Framebuffer const& framebuffer);
	void EndRenderPass(void);

	void SetViewport(::VkViewport const& viewport);
	void SetScissor(::VkRect2D const& scissor_rect);

	void BindPipeline(
		::VkPipelineBindPoint pipeline_bind_point,
		::VkPipeline          pipeline);

	void PushDescriptorSet(
		::VkDevice                                   device,
		::VkPipelineBindPoint                        pipeline_bind_point,
		::VkPipelineLayout                           layout,
		bksge::uint32_t                              set,
		bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes);

public:
	operator ::VkCommandBuffer() const;
public:
	::VkCommandBuffer const* GetAddressOf(void) const;

private:
	// noncopyable
	CommandBuffer(CommandBuffer const&) = delete;
	CommandBuffer& operator=(CommandBuffer const&) = delete;

private:
	vulkan::CommandPoolSharedPtr	m_command_pool;
	::VkCommandBuffer				m_command_buffer;
};

bksge::unique_ptr<vulkan::CommandBuffer>
BeginSingleTimeCommands(
	vulkan::CommandPoolSharedPtr const& command_pool);

void
EndSingleTimeCommands(
	vulkan::CommandPoolSharedPtr const& command_pool,
	bksge::unique_ptr<vulkan::CommandBuffer> const& command_buffer);

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/command_buffer_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_COMMAND_BUFFER_HPP
