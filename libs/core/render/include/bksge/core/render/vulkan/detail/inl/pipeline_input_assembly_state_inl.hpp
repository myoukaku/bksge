/**
 *	@file	pipeline_input_assembly_state_inl.hpp
 *
 *	@brief	PipelineInputAssemblyState の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_INPUT_ASSEMBLY_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_INPUT_ASSEMBLY_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/pipeline_input_assembly_state.hpp>
#include <bksge/core/render/vulkan/detail/primitive_topology.hpp>
#include <bksge/core/render/primitive_topology.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
PipelineInputAssemblyState::PipelineInputAssemblyState(
	bksge::PrimitiveTopology const& primitive_topology)
{
	m_input_assembly_state.topology =
		vulkan::PrimitiveTopology(primitive_topology);
}

BKSGE_INLINE ::VkPipelineInputAssemblyStateCreateInfo const*
PipelineInputAssemblyState::GetAddressOf(void) const
{
	return &m_input_assembly_state;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_PIPELINE_INPUT_ASSEMBLY_STATE_INL_HPP
