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
#include <bksge/core/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <memory>

namespace bksge
{

namespace render
{

namespace vk
{

BKSGE_INLINE
PipelineDynamicStateCreateInfo::PipelineDynamicStateCreateInfo(void)
{
	sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	pNext             = nullptr;
	flags             = 0;
	dynamicStateCount = 0;
	pDynamicStates    = nullptr;
}

BKSGE_INLINE
PipelineVertexInputStateCreateInfo::PipelineVertexInputStateCreateInfo(void)
{
	sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	pNext                           = nullptr;
	flags                           = 0;
	vertexBindingDescriptionCount   = 0;
	pVertexBindingDescriptions      = nullptr;
	vertexAttributeDescriptionCount = 0;
	pVertexAttributeDescriptions    = nullptr;
}

BKSGE_INLINE
PipelineInputAssemblyStateCreateInfo::PipelineInputAssemblyStateCreateInfo(void)
{
	sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	pNext                  = nullptr;
	flags                  = 0;
	topology               = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
	primitiveRestartEnable = VK_FALSE;
}

BKSGE_INLINE
PipelineRasterizationStateCreateInfo::PipelineRasterizationStateCreateInfo(void)
{
	sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	pNext                   = nullptr;
	flags                   = 0;
	depthClampEnable        = VK_FALSE;
	rasterizerDiscardEnable = VK_FALSE;
	polygonMode             = VK_POLYGON_MODE_FILL;
	cullMode                = 0;
	frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	depthBiasEnable         = VK_FALSE;
	depthBiasConstantFactor = 0;
	depthBiasClamp          = 0;
	depthBiasSlopeFactor    = 0;
	lineWidth               = 0;
}

BKSGE_INLINE
PipelineColorBlendAttachmentState::PipelineColorBlendAttachmentState(void)
{
	blendEnable         = VK_FALSE;
	srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendOp        = VK_BLEND_OP_ADD;
	srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	alphaBlendOp        = VK_BLEND_OP_ADD;
	colorWriteMask      = 0;
}

BKSGE_INLINE
PipelineColorBlendStateCreateInfo::PipelineColorBlendStateCreateInfo(void)
{
	sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	pNext             = nullptr;
	flags             = 0;
	logicOpEnable     = VK_FALSE;
	logicOp           = VK_LOGIC_OP_CLEAR;
	attachmentCount   = 0;
	pAttachments      = nullptr;
	blendConstants[0] = 0;
	blendConstants[1] = 0;
	blendConstants[2] = 0;
	blendConstants[3] = 0;
}

BKSGE_INLINE
PipelineViewportStateCreateInfo::PipelineViewportStateCreateInfo(void)
{
	sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	pNext         = nullptr;
	flags         = 0;
	viewportCount = 0;
	pViewports    = nullptr;
	scissorCount  = 0;
	pScissors     = nullptr;
}

BKSGE_INLINE
PipelineDepthStencilStateCreateInfo::PipelineDepthStencilStateCreateInfo(void)
{
	sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	pNext                 = nullptr;
	flags                 = 0;
	depthTestEnable       = VK_FALSE;
	depthWriteEnable      = VK_FALSE;
	depthCompareOp        = VK_COMPARE_OP_NEVER;
	depthBoundsTestEnable = VK_FALSE;
	stencilTestEnable     = VK_FALSE;
	stencilTestEnable     = VK_FALSE;

	front.failOp           = VK_STENCIL_OP_KEEP;
	front.passOp           = VK_STENCIL_OP_KEEP;
	front.compareOp        = VK_COMPARE_OP_NEVER;
	front.compareMask      = 0;
	front.reference        = 0;
	front.depthFailOp      = VK_STENCIL_OP_KEEP;
	front.writeMask        = 0;

	back.failOp           = VK_STENCIL_OP_KEEP;
	back.passOp           = VK_STENCIL_OP_KEEP;
	back.compareOp        = VK_COMPARE_OP_NEVER;
	back.compareMask      = 0;
	back.reference        = 0;
	back.depthFailOp      = VK_STENCIL_OP_KEEP;
	back.writeMask        = 0;

	minDepthBounds        = 0;
	maxDepthBounds        = 0;
}

BKSGE_INLINE
PipelineMultisampleStateCreateInfo::PipelineMultisampleStateCreateInfo(void)
{
	sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	pNext                 = nullptr;
	flags                 = 0;
	rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
	sampleShadingEnable   = VK_FALSE;
	minSampleShading      = 0.0f;
	pSampleMask           = nullptr;
	alphaToCoverageEnable = VK_FALSE;
	alphaToOneEnable      = VK_FALSE;
}

BKSGE_INLINE
GraphicsPipelineCreateInfo::GraphicsPipelineCreateInfo(void)
{
	sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pNext               = nullptr;
	flags               = 0;
	stageCount          = 0;
	pStages             = nullptr;
	pVertexInputState   = nullptr;
	pInputAssemblyState = nullptr;
	pTessellationState  = nullptr;
	pViewportState      = nullptr;
	pRasterizationState = nullptr;
	pMultisampleState   = nullptr;
	pDepthStencilState  = nullptr;
	pColorBlendState    = nullptr;
	pDynamicState       = nullptr;
	layout              = VK_NULL_HANDLE;
	renderPass          = VK_NULL_HANDLE;
	subpass             = 0;
	basePipelineHandle  = VK_NULL_HANDLE;
	basePipelineIndex   = 0;
}

BKSGE_INLINE
GraphicsPipeline::GraphicsPipeline(
	std::shared_ptr<vk::Device> const& device,
	vk::PipelineCache const& cache,
	vk::GraphicsPipelineCreateInfo const& info)
	: m_pipeline(VK_NULL_HANDLE)
	, m_device(device)
{
	vk::CreateGraphicsPipelines(*m_device, cache, 1, &info, nullptr, &m_pipeline);
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

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GRAPHICS_PIPELINE_INL_HPP
