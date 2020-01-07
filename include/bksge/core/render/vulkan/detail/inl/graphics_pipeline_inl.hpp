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
#include <bksge/core/render/vulkan/detail/pipeline_cache.hpp>
#include <bksge/core/render/vulkan/detail/pipeline_layout.hpp>
#include <bksge/core/render/vulkan/detail/rasterizer_state.hpp>
#include <bksge/core/render/vulkan/detail/depth_stencil_state.hpp>
#include <bksge/core/render/vulkan/detail/blend_state.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/render_state.hpp>
#include <bksge/core/render/geometry.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <memory>
#include <vector>

namespace bksge
{

namespace render
{

namespace vulkan
{

inline ::VkFormat
ToVkFormat(bksge::TypeEnum type, std::size_t num)
{
	switch (type)
	{
	case bksge::TypeEnum::kSInt8:
		switch (num)
		{
		case 1: return VK_FORMAT_R8_SINT;
		case 2: return VK_FORMAT_R8G8_SINT;
		case 3: return VK_FORMAT_R8G8B8_SINT;
		case 4: return VK_FORMAT_R8G8B8A8_SINT;
		}
	case bksge::TypeEnum::kUInt8:
		switch (num)
		{
		case 1: return VK_FORMAT_R8_UINT;
		case 2: return VK_FORMAT_R8G8_UINT;
		case 3: return VK_FORMAT_R8G8B8_UINT;
		case 4: return VK_FORMAT_R8G8B8A8_UINT;
		}
	case bksge::TypeEnum::kSInt16:
		switch (num)
		{
		case 1: return VK_FORMAT_R16_SINT;
		case 2: return VK_FORMAT_R16G16_SINT;
		case 3: return VK_FORMAT_R16G16B16_SINT;
		case 4: return VK_FORMAT_R16G16B16A16_SINT;
		}
	case bksge::TypeEnum::kUInt16:
		switch (num)
		{
		case 1: return VK_FORMAT_R16_UINT;
		case 2: return VK_FORMAT_R16G16_UINT;
		case 3: return VK_FORMAT_R16G16B16_UINT;
		case 4: return VK_FORMAT_R16G16B16A16_UINT;
		}
	case bksge::TypeEnum::kSInt32:
		switch (num)
		{
		case 1: return VK_FORMAT_R32_SINT;
		case 2: return VK_FORMAT_R32G32_SINT;
		case 3: return VK_FORMAT_R32G32B32_SINT;
		case 4: return VK_FORMAT_R32G32B32A32_SINT;
		}
	case bksge::TypeEnum::kUInt32:
		switch (num)
		{
		case 1: return VK_FORMAT_R32_UINT;
		case 2: return VK_FORMAT_R32G32_UINT;
		case 3: return VK_FORMAT_R32G32B32_UINT;
		case 4: return VK_FORMAT_R32G32B32A32_UINT;
		}
	case bksge::TypeEnum::kFloat:
		switch (num)
		{
		case 1: return VK_FORMAT_R32_SFLOAT;
		case 2: return VK_FORMAT_R32G32_SFLOAT;
		case 3: return VK_FORMAT_R32G32B32_SFLOAT;
		case 4: return VK_FORMAT_R32G32B32A32_SFLOAT;
		}
	}
	return VK_FORMAT_UNDEFINED;
}

BKSGE_INLINE
GraphicsPipeline::GraphicsPipeline(
	vulkan::DeviceSharedPtr const& device,
	::VkSampleCountFlagBits num_samples,
	bksge::Geometry const& geometry,
	vulkan::RenderPass const& render_pass,
	vulkan::Shader const& shader,
	bksge::RenderState const& render_state)
	: m_device(device)
	, m_pipeline(VK_NULL_HANDLE)
{
	m_pipeline_cache =
		bksge::make_unique<vulkan::PipelineCache>(m_device);

	m_pipeline_layout =
		bksge::make_unique<vulkan::PipelineLayout>(
			m_device,
			shader.GetDescriptorSetLayout());

	auto const& layout = geometry.vertex_layout();
	auto const stride = layout.total_bytes();

	::VkVertexInputBindingDescription vi_binding;
	vi_binding.binding   = 0;
	vi_binding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	vi_binding.stride    = static_cast<std::uint32_t>(stride);

	std::vector<::VkVertexInputAttributeDescription> vi_attribs;

	for (auto& attribute : layout.vertex_attribute_array())
	{
		::VkVertexInputAttributeDescription a;
		a.binding  = 0;
		a.location = static_cast<std::uint32_t>(vi_attribs.size());
		a.format   = ToVkFormat(attribute.type(), attribute.element_num());
		a.offset   = static_cast<std::uint32_t>(attribute.offset());
		vi_attribs.push_back(a);
	}

	std::vector<::VkDynamicState> dynamic_states;

	vk::PipelineVertexInputStateCreateInfo vertex_input_state;
	vertex_input_state.SetVertexBindingDescription(&vi_binding);
	vertex_input_state.SetVertexAttributeDescriptions(vi_attribs);

	vk::PipelineInputAssemblyStateCreateInfo input_assembly_state;
	input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	vulkan::RasterizerState raster_state(render_state.rasterizer_state());

	vulkan::BlendState color_blend_state(render_state.blend_state());

	vk::PipelineViewportStateCreateInfo viewport_state;
#if !defined(__ANDROID__)
	viewport_state.viewportCount = 1;//NUM_VIEWPORTS;
	viewport_state.scissorCount  = 1;//NUM_SCISSORS;
	viewport_state.pScissors     = nullptr;
	viewport_state.pViewports    = nullptr;
	dynamic_states.push_back(VK_DYNAMIC_STATE_VIEWPORT);
	dynamic_states.push_back(VK_DYNAMIC_STATE_SCISSOR);
#else
	// Temporary disabling dynamic viewport on Android because some of drivers doesn't
	// support the feature.
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

	vulkan::DepthStencilState depth_stencil_state(render_state.depth_state(), render_state.stencil_state());

	vk::PipelineMultisampleStateCreateInfo multisample_state;
	multisample_state.pSampleMask           = nullptr;
	multisample_state.rasterizationSamples  = num_samples;
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
	pipeline.pVertexInputState   = &vertex_input_state;
	pipeline.pInputAssemblyState = &input_assembly_state;
	pipeline.pRasterizationState = raster_state.GetAddressOf();
	pipeline.pColorBlendState    = color_blend_state.GetAddressOf();
	pipeline.pTessellationState  = nullptr;
	pipeline.pMultisampleState   = &multisample_state;
	pipeline.pDynamicState       = &dynamic_state_ci;
	pipeline.pViewportState      = &viewport_state;
	pipeline.pDepthStencilState  = depth_stencil_state.GetAddressOf();
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

BKSGE_INLINE ::VkPipelineLayout
GraphicsPipeline::GetLayout(void) const
{
	return *m_pipeline_layout;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GRAPHICS_PIPELINE_INL_HPP
