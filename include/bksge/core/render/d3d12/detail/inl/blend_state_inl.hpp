/**
 *	@file	blend_state_inl.hpp
 *
 *	@brief	BlendState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_STATE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/blend_state.hpp>
#include <bksge/core/render/d3d12/detail/blend_factor.hpp>
#include <bksge/core/render/d3d12/detail/blend_operation.hpp>
#include <bksge/core/render/d3d12/detail/bool.hpp>
#include <bksge/core/render/d3d12/detail/color_write_flag.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/blend_state.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
BlendState::BlendState(bksge::BlendState const& blend_state)
	: m_desc{}
{
	m_desc.AlphaToCoverageEnable  = FALSE;
	m_desc.IndependentBlendEnable = FALSE;
	for (auto& rt : m_desc.RenderTarget)
	{
		rt.BlendEnable           = d3d12::Bool(blend_state.enable());
		rt.SrcBlend              = d3d12::BlendFactor(blend_state.color_src_factor());
		rt.DestBlend             = d3d12::BlendFactor(blend_state.color_dst_factor());
		rt.BlendOp               = d3d12::BlendOperation(blend_state.color_operation());
		rt.SrcBlendAlpha         = d3d12::BlendFactor(blend_state.alpha_src_factor());
		rt.DestBlendAlpha        = d3d12::BlendFactor(blend_state.alpha_dst_factor());
		rt.BlendOpAlpha          = d3d12::BlendOperation(blend_state.alpha_operation());
		rt.RenderTargetWriteMask = d3d12::ColorWriteFlag(blend_state.color_write_mask());
		rt.LogicOpEnable         = FALSE;
		rt.LogicOp               = D3D12_LOGIC_OP_NOOP;
	}
}

BKSGE_INLINE
BlendState::operator ::D3D12_BLEND_DESC() const
{
	return m_desc;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_BLEND_STATE_INL_HPP
