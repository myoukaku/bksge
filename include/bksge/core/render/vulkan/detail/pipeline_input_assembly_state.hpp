/**
 *	@file	pipeline_input_assembly_state.hpp
 *
 *	@brief	PipelineInputAssemblyState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_INPUT_ASSEMBLY_STATE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_INPUT_ASSEMBLY_STATE_HPP

#include <bksge/core/render/vulkan/detail/fwd/pipeline_input_assembly_state_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/fwd/primitive_topology_fwd.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class PipelineInputAssemblyState
{
public:
	explicit PipelineInputAssemblyState(
		bksge::PrimitiveTopology const& primitive_topology);

	::VkPipelineInputAssemblyStateCreateInfo const* GetAddressOf(void) const;

private:
	vk::PipelineInputAssemblyStateCreateInfo m_input_assembly_state;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/pipeline_input_assembly_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_PIPELINE_INPUT_ASSEMBLY_STATE_HPP
