﻿/**
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
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/vector.hpp>

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
	: m_device(device)
	, m_pipeline(VK_NULL_HANDLE)
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

	vk::GraphicsPipelineCreateInfo pipeline;
	pipeline.layout              = *m_pipeline_layout;
	pipeline.basePipelineHandle  = VK_NULL_HANDLE;
	pipeline.basePipelineIndex   = 0;
	pipeline.pVertexInputState   = vertex_input_state.GetAddressOf();
	pipeline.pInputAssemblyState = input_assembly_state.GetAddressOf();
	pipeline.pRasterizationState = render_state.rasterizer_state().GetAddressOf();
	pipeline.pColorBlendState    = render_state.blend_state().GetAddressOf();
	pipeline.pTessellationState  = nullptr;
	pipeline.pMultisampleState   = &multisample_state;
	pipeline.pDynamicState       = &dynamic_state_ci;
	pipeline.pViewportState      = &viewport_state;
	pipeline.pDepthStencilState  = render_state.depth_stencil_state().GetAddressOf();
	pipeline.SetStages(shader.GetStages());
	pipeline.renderPass          = render_pass;
	pipeline.subpass             = 0;

	vk::CreateGraphicsPipelines(
		*m_device,
		*m_pipeline_cache,
		1,
		&pipeline,
		nullptr,
		&m_pipeline);
}

BKSGE_INLINE
GraphicsPipeline::~GraphicsPipeline()
{
	vk::DestroyPipeline(*m_device, m_pipeline, nullptr);
}

BKSGE_INLINE
GraphicsPipeline::operator ::VkPipeline() const
{
	return m_pipeline;
}

BKSGE_INLINE vulkan::PipelineLayout const&
GraphicsPipeline::pipeline_layout(void) const
{
	return *m_pipeline_layout;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GRAPHICS_PIPELINE_INL_HPP
