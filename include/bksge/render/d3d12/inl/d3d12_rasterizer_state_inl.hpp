﻿/**
 *	@file	d3d12_rasterizer_state_inl.hpp
 *
 *	@brief	D3D12RasterizerState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_RASTERIZER_STATE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_RASTERIZER_STATE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_rasterizer_state.hpp>
#include <bksge/render/d3d12/d3d12_fill_mode.hpp>
#include <bksge/render/d3d12/d3d12_cull_mode.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/rasterizer_state.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12RasterizerState::D3D12RasterizerState(RasterizerState const& state)
	: m_desc{}
{
	m_desc.FillMode              = ToD3D12FillMode(state.fill_mode());
	m_desc.CullMode              = ToD3D12CullMode(state.cull_mode());
	m_desc.FrontCounterClockwise = (state.front_face() == FrontFace::kCounterClockwise);
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
D3D12RasterizerState::operator ::D3D12_RASTERIZER_DESC() const
{
	return m_desc;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_RASTERIZER_STATE_INL_HPP
