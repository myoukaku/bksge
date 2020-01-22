/**
 *	@file	depth_stencil_state_inl.hpp
 *
 *	@brief	DepthStencilState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/depth_stencil_state.hpp>
#include <bksge/core/render/d3d12/detail/comparison_function.hpp>
#include <bksge/core/render/d3d12/detail/bool.hpp>
#include <bksge/core/render/d3d12/detail/depth_write_mask.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE
DepthStencilState::DepthStencilState(
	bksge::DepthState const& depth_state,
	bksge::StencilState const& stencil_state)
	: m_desc{}
{
	m_desc.DepthEnable                  = d3d12::Bool(depth_state.enable());
	m_desc.DepthWriteMask               = d3d12::DepthWriteMask(depth_state.write());
	m_desc.DepthFunc                    = d3d12::ComparisonFunction(depth_state.func());
	m_desc.StencilEnable                = d3d12::Bool(stencil_state.enable());
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
DepthStencilState::operator ::D3D12_DEPTH_STENCIL_DESC() const
{
	return m_desc;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP
