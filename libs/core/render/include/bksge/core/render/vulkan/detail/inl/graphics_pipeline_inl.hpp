/**
 *	@file	graphics_pipeline_inl.hpp
 *
 *	@brief	GraphicsPipeline クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GRAPHICS_PIPELINE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GRAPHICS_PIPELINE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/graphics_pipeline.hpp>
#include <bksge/core/render/vulkan/detail/device.hpp>
#include <bksge/core/render/vulkan/detail/render_pass.hpp>
#include <bksge/core/render/vulkan/detail/shader.hpp>
#include <bksge/core/render/vulkan/detail/render_state.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_input_assembly_state.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_vertex_input_state.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_layout.hpp>
#include <bksge/core/render/vulkan/detail/rasterizer_state.hpp>
#include <bksge/core/render/vulkan/detail/depth_stencil_state.hpp>
#include <bksge/core/render/vulkan/detail/blend_state.hpp>
#include <bksge/core/render/vulkan/detail/primitive_topology.hpp>
#include <bksge/core/render/vulkan/detail/command_buffer.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
GraphicsPipeline::GraphicsPipeline(
	vulkan::DeviceSharedPtr const& device,
	vulkan::RenderPass const& render_pass,
	vulkan::PipelineInputAssemblyState const& input_assembly_state,
	vulkan::PipelineVertexInputState const& vertex_input_state,
	vulkan::Shader const& shader,
	vulkan::RenderState const& render_state)
	: m_pipeline(VK_NULL_HANDLE)
	, m_device(device)
{
	m_pipeline_cache =
		bksge::make_unique<vulkan::PipelineCache>(m_device);

	m_pipeline_layout =
		bksge::make_unique<vulkan::PipelineLayout>(
			m_device,
			shader.GetDescriptorSetLayout());

	bksge::vector<::VkDynamicState> dynamic_states;

	vk::PipelineViewportStateCreateInfo viewport_state;
#if !defined(__ANDROID__)
	viewport_state.viewportCount = 1;//NUM_VIEWPORTS;
	viewport_state.scissorCount  = 1;//NUM_SCISSORS;
	viewport_state.pScissors     = nullptr;
	viewport_state.pViewports    = nullptr;
	dynamic_states.push_back(VK_DYNAMIC_STATE_VIEWPORT);
	dynamic_states.push_back(VK_DYNAMIC_STATE_SCISSOR);
#else
	VkViewport viewports;
	viewports.minDepth = 0.0f;
	viewports.maxDepth = 1.0f;
	viewports.x        = 0;
	viewports.y        = 0;
	viewports.width    = info.width;
	viewports.height   = info.height;
	VkRect2D scissor;
	scissor.extent.width  = info.width;
	scissor.extent.height = info.height;
	scissor.offset.x      = 0;
	scissor.offset.y      = 0;
	viewport_state.viewportCount = NUM_VIEWPORTS;
	viewport_state.scissorCount  = NUM_SCISSORS;
	viewport_state.pScissors     = &scissor;
	viewport_state.pViewports    = &viewports;
#endif

	vk::PipelineMultisampleStateCreateInfo multisample_state;
	multisample_state.pSampleMask           = nullptr;
	multisample_state.rasterizationSamples  = render_pass.samples();
	multisample_state.sampleShadingEnable   = VK_FALSE;
	multisample_state.alphaToCoverageEnable = VK_FALSE;
	multisample_state.alphaToOneEnable      = VK_FALSE;
	multisample_state.minSampleShading      = 0.0;

	vk::PipelineDynamicStateCreateInfo dynamic_state_ci;
	dynamic_state_ci.SetDynamicStates(dynamic_states);

	vk::GraphicsPipelineCreateInfo create_info;
	create_info.layout              = *m_pipeline_layout;
	create_info.basePipelineHandle  = VK_NULL_HANDLE;
	create_info.basePipelineIndex   = 0;
	create_info.pVertexInputState   = vertex_input_state.GetAddressOf();
	create_info.pInputAssemblyState = input_assembly_state.GetAddressOf();
	create_info.pRasterizationState = render_state.rasterizer_state().GetAddressOf();
	create_info.pColorBlendState    = render_state.blend_state().GetAddressOf();
	create_info.pTessellationState  = nullptr;
	create_info.pMultisampleState   = &multisample_state;
	create_info.pDynamicState       = &dynamic_state_ci;
	create_info.pViewportState      = &viewport_state;
	create_info.pDepthStencilState  = render_state.depth_stencil_state().GetAddressOf();
	create_info.SetStages(shader.GetStages());
	create_info.renderPass          = render_pass;
	create_info.subpass             = 0;

	m_pipeline = m_device->CreateGraphicsPipeline(*m_pipeline_cache, create_info);
}

BKSGE_INLINE
GraphicsPipeline::~GraphicsPipeline()
{
	m_device->DestroyPipeline(m_pipeline);
}

BKSGE_INLINE void
GraphicsPipeline::Bind(vulkan::CommandBuffer* command_buffer)
{
	command_buffer->BindPipeline(
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		m_pipeline);
}

BKSGE_INLINE void
GraphicsPipeline::PushDescriptorSet(
	vulkan::CommandBuffer* command_buffer,
	std::uint32_t set,
	bksge::vector<::VkWriteDescriptorSet> const& descriptor_writes)
{
	command_buffer->PushDescriptorSet(
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		*m_pipeline_layout,
		set,
		descriptor_writes);
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GRAPHICS_PIPELINE_INL_HPP
