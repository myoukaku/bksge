/**
 *	@file	rasterizer_state_inl.hpp
 *
 *	@brief	RasterizerState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RASTERIZER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RASTERIZER_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/rasterizer_state.hpp>
#include <bksge/core/render/d3d11/detail/fill_mode.hpp>
#include <bksge/core/render/d3d11/detail/cull_mode.hpp>
#include <bksge/core/render/d3d11/detail/front_counter_clockwise.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
RasterizerState::RasterizerState(bksge::RasterizerState const& state)
	: m_desc{}
{
	m_desc.FillMode              = d3d11::FillMode(state.fill_mode());
	m_desc.CullMode              = d3d11::CullMode(state.cull_mode());
	m_desc.FrontCounterClockwise = d3d11::FrontCounterClockwise(state.front_face());
	m_desc.DepthBias             = D3D11_DEFAULT_DEPTH_BIAS;
	m_desc.DepthBiasClamp        = D3D11_DEFAULT_DEPTH_BIAS_CLAMP;
	m_desc.SlopeScaledDepthBias  = D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	m_desc.DepthClipEnable       = FALSE;
	m_desc.ScissorEnable         = TRUE;	// シザーテストは常に有効(他のプラットフォームと動作を合わせるため)
	m_desc.MultisampleEnable     = FALSE;
	m_desc.AntialiasedLineEnable = FALSE;
}

BKSGE_INLINE
RasterizerState::operator ::D3D11_RASTERIZER_DESC() const
{
	return m_desc;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_RASTERIZER_STATE_INL_HPP
