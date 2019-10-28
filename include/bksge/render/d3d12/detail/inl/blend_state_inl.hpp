﻿/**
 *	@file	blend_state_inl.hpp
 *
 *	@brief	BlendState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_BLEND_STATE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_BLEND_STATE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/blend_state.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
BlendState::BlendState()
	: m_desc{}
{
	m_desc.AlphaToCoverageEnable  = false;
	m_desc.IndependentBlendEnable = false;
	m_desc.RenderTarget[0].BlendEnable           = false;
	m_desc.RenderTarget[0].LogicOpEnable         = false;
	m_desc.RenderTarget[0].SrcBlend              = D3D12_BLEND_ONE;
	m_desc.RenderTarget[0].DestBlend             = D3D12_BLEND_ZERO;
	m_desc.RenderTarget[0].BlendOp               = D3D12_BLEND_OP_ADD;
	m_desc.RenderTarget[0].SrcBlendAlpha         = D3D12_BLEND_ONE;
	m_desc.RenderTarget[0].DestBlendAlpha        = D3D12_BLEND_ZERO;
	m_desc.RenderTarget[0].BlendOpAlpha          = D3D12_BLEND_OP_ADD;
	m_desc.RenderTarget[0].LogicOp               = D3D12_LOGIC_OP_NOOP;
	m_desc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
}

BKSGE_INLINE
BlendState::operator ::D3D12_BLEND_DESC() const
{
	return m_desc;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_BLEND_STATE_INL_HPP