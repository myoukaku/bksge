/**
 *	@file	d3d12_depth_stencil_state_inl.hpp
 *
 *	@brief	D3D12DepthStencilState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_DEPTH_STENCIL_STATE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_DEPTH_STENCIL_STATE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_depth_stencil_state.hpp>
#include <bksge/render/d3d12/d3d12.hpp>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D12DepthStencilState::D3D12DepthStencilState()
	: m_desc{}
{
	m_desc.DepthEnable                  = FALSE;
//	m_desc.DepthWriteMask               = D3D12_DEPTH_WRITE_MASK_ZERO;
//	m_desc.DepthFunc                    = D3D12_COMPARISON_FUNC_NEVER;
	m_desc.StencilEnable                = FALSE;
//	m_desc.StencilReadMask              = 0u;
//	m_desc.StencilWriteMask             = 0u;
//	m_desc.FrontFace.StencilFailOp      = D3D12_STENCIL_OP_KEEP;
//	m_desc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
//	m_desc.FrontFace.StencilPassOp      = D3D12_STENCIL_OP_KEEP;
//	m_desc.FrontFace.StencilFunc        = D3D12_COMPARISON_FUNC_NEVER;
//	m_desc.BackFace.StencilFailOp       = D3D12_STENCIL_OP_KEEP;
//	m_desc.BackFace.StencilDepthFailOp  = D3D12_STENCIL_OP_KEEP;
//	m_desc.BackFace.StencilPassOp       = D3D12_STENCIL_OP_KEEP;
//	m_desc.BackFace.StencilFunc         = D3D12_COMPARISON_FUNC_NEVER;
}

BKSGE_INLINE
D3D12DepthStencilState::operator ::D3D12_DEPTH_STENCIL_DESC() const
{
	return m_desc;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_DEPTH_STENCIL_STATE_INL_HPP
