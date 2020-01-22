/**
 *	@file	rasterizer_state_inl.hpp
 *
 *	@brief	RasterizerState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RASTERIZER_STATE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RASTERIZER_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/rasterizer_state.hpp>
#include <bksge/core/render/d3d12/detail/fill_mode.hpp>
#include <bksge/core/render/d3d12/detail/cull_mode.hpp>
#include <bksge/core/render/d3d12/detail/front_counter_clockwise.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
RasterizerState::RasterizerState(bksge::RasterizerState const& state)
	: m_desc{}
{
	m_desc.FillMode              = d3d12::FillMode(state.fill_mode());
	m_desc.CullMode              = d3d12::CullMode(state.cull_mode());
	m_desc.FrontCounterClockwise = d3d12::FrontCounterClockwise(state.front_face());
	m_desc.DepthBias             = D3D12_DEFAULT_DEPTH_BIAS;
	m_desc.DepthBiasClamp        = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	m_desc.SlopeScaledDepthBias  = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	m_desc.DepthClipEnable       = true;
	m_desc.MultisampleEnable     = false;
	m_desc.AntialiasedLineEnable = false;
	m_desc.ForcedSampleCount     = 0;
	m_desc.ConservativeRaster    = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
}

BKSGE_INLINE
RasterizerState::operator ::D3D12_RASTERIZER_DESC() const
{
	return m_desc;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_RASTERIZER_STATE_INL_HPP
