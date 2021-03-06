﻿/**
 *	@file	graphics_pipeline.hpp
 *
 *	@brief	GraphicsPipeline クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP

#include <bksge/core/render/vulkan/detail/fwd/graphics_pipeline_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/command_buffer_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/device_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/pipeline_input_assembly_state_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/pipeline_vertex_input_state_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/pipeline_cache_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/pipeline_layout_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_pass_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/render_state_fwd.hpp>
#include <bksge/core/render/vulkan/detail/fwd/shader_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class GraphicsPipeline
{
public:
	explicit GraphicsPipeline(
		vulkan::DeviceSharedPtr const& device,
		vulkan::RenderPass const& render_pass,
		vulkan::PipelineInputAssemblyState const& input_assembly_state,
		vulkan::PipelineVertexInputState const& vertex_input_state,
		vulkan::Shader const& shader,
		vulkan::RenderState const& render_state);

	~GraphicsPipeline();

	void Bind(vulkan::CommandBuffer* command_buffer);

	void PushDescriptorSet(
		vulkan::CommandBuffer* command_buffer,
		bksge::uint32_t set,
		bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes);

private:
	// noncopyable
	GraphicsPipeline(GraphicsPipeline const&) = delete;
	GraphicsPipeline& operator=(GraphicsPipeline const&) = delete;

private:
	::VkPipeline					m_pipeline;
	vulkan::DeviceSharedPtr			m_device;
	vulkan::PipelineCacheUniquePtr	m_pipeline_cache;
	vulkan::PipelineLayoutUniquePtr	m_pipeline_layout;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/graphics_pipeline_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_GRAPHICS_PIPELINE_HPP
