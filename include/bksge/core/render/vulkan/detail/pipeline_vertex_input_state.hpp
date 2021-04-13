/**
 *	@file	pipeline_vertex_input_state.hpp
 *
 *	@brief	PipelineVertexInputState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_VERTEX_INPUT_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_VERTEX_INPUT_STATE_HPP

#include <bksge/core/render/vulkan/detail/fwd/pipeline_vertex_input_state_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/vertex_layout_fwd.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class PipelineVertexInputState
{
public:
	explicit PipelineVertexInputState(bksge::VertexLayout const& vertex_layout);

	::VkPipelineVertexInputStateCreateInfo const* GetAddressOf(void) const;

private:
	vk::PipelineVertexInputStateCreateInfo				m_vertex_input_state;
	::VkVertexInputBindingDescription					m_binding_descriptions;
	bksge::vector<::VkVertexInputAttributeDescription>	m_attribute_description;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/pipeline_vertex_input_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_VERTEX_INPUT_STATE_HPP
