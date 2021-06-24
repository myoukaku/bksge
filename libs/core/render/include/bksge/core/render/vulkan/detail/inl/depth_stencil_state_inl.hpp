/**
 *	@file	depth_stencil_state_inl.hpp
 *
 *	@brief	DepthStencilState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/depth_stencil_state.hpp>
#include <bksge/core/render/vulkan/detail/comparison_function.hpp>
#include <bksge/core/render/vulkan/detail/stencil_operation.hpp>
#include <bksge/core/render/vulkan/detail/bool.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

BKSGE_INLINE
DepthStencilState::DepthStencilState(
	bksge::DepthState const& depth_state,
	bksge::StencilState const& stencil_state)
{
	auto& ds = m_depth_stencil_state;
	ds.depthTestEnable       = vulkan::Bool(depth_state.enable());
	ds.depthWriteEnable      = vulkan::Bool(depth_state.write());
	ds.depthCompareOp        = vulkan::ComparisonFunction(depth_state.func());
	ds.depthBoundsTestEnable = VK_FALSE;
	ds.stencilTestEnable     = vulkan::Bool(stencil_state.enable());
	ds.back.failOp           = vulkan::StencilOperation(stencil_state.fail_operation());
	ds.back.passOp           = vulkan::StencilOperation(stencil_state.pass_operation());
	ds.back.compareOp        = vulkan::ComparisonFunction(stencil_state.func());
	ds.back.compareMask      = stencil_state.read_mask();
	ds.back.reference        = stencil_state.reference();
	ds.back.depthFailOp      = vulkan::StencilOperation(stencil_state.depth_fail_operation());
	ds.back.writeMask        = stencil_state.write_mask();
	ds.minDepthBounds        = 0;
	ds.maxDepthBounds        = 0;
	ds.front                 = ds.back;
}

BKSGE_INLINE ::VkPipelineDepthStencilStateCreateInfo const*
DepthStencilState::GetAddressOf(void) const
{
	return &m_depth_stencil_state;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP
