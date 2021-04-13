/**
 *	@file	pipeline_vertex_input_state_inl.hpp
 *
 *	@brief	PipelineVertexInputState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_VERTEX_INPUT_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_VERTEX_INPUT_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/pipeline_vertex_input_state.hpp>
#include <bksge/core/render/vulkan/detail/vertex_format.hpp>
#include <bksge/core/render/vertex_layout.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
PipelineVertexInputState::PipelineVertexInputState(
	bksge::VertexLayout const& vertex_layout)
{
	auto const stride = vertex_layout.total_bytes();

	m_binding_descriptions.binding   = 0;
	m_binding_descriptions.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	m_binding_descriptions.stride    = static_cast<bksge::uint32_t>(stride);

	for (auto& attribute : vertex_layout.vertex_attribute_array())
	{
		::VkVertexInputAttributeDescription desc;
		desc.binding  = 0;
		desc.location = static_cast<bksge::uint32_t>(m_attribute_description.size());
		desc.format   = vulkan::VertexFormat(attribute);
		desc.offset   = static_cast<bksge::uint32_t>(attribute.offset());
		m_attribute_description.push_back(desc);
	}

	m_vertex_input_state.SetVertexBindingDescription(&m_binding_descriptions);
	m_vertex_input_state.SetVertexAttributeDescriptions(m_attribute_description);
}

BKSGE_INLINE ::VkPipelineVertexInputStateCreateInfo const*
PipelineVertexInputState::GetAddressOf(void) const
{
	return &m_vertex_input_state;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_VERTEX_INPUT_STATE_INL_HPP
