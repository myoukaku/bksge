/**
 *	@file	depth_stencil_state_inl.hpp
 *
 *	@brief	DepthStencilState クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/depth_stencil_state.hpp>
#include <bksge/core/render/d3d11/detail/comparison_function.hpp>
#include <bksge/core/render/d3d11/detail/stencil_operation.hpp>
#include <bksge/core/render/d3d11/detail/bool.hpp>
#include <bksge/core/render/d3d11/detail/depth_write_mask.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/depth_state.hpp>
#include <bksge/core/render/stencil_state.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

BKSGE_INLINE
DepthStencilState::DepthStencilState(
	bksge::DepthState const& depth_state,
	bksge::StencilState const& stencil_state)
	: m_desc{}
{
	m_desc.DepthEnable                  = d3d11::Bool(depth_state.enable());
	m_desc.DepthWriteMask               = d3d11::DepthWriteMask(depth_state.write());
	m_desc.DepthFunc                    = d3d11::ComparisonFunction(depth_state.func());
	m_desc.StencilEnable                = d3d11::Bool(stencil_state.enable());
	m_desc.StencilReadMask              = stencil_state.read_mask();
	m_desc.StencilWriteMask             = stencil_state.write_mask();
	m_desc.BackFace.StencilFailOp       = d3d11::StencilOperation(stencil_state.fail_operation());
	m_desc.BackFace.StencilDepthFailOp  = d3d11::StencilOperation(stencil_state.depth_fail_operation());
	m_desc.BackFace.StencilPassOp       = d3d11::StencilOperation(stencil_state.pass_operation());
	m_desc.BackFace.StencilFunc         = d3d11::ComparisonFunction(stencil_state.func());
	m_desc.FrontFace = m_desc.BackFace;
}

BKSGE_INLINE
DepthStencilState::operator ::D3D11_DEPTH_STENCIL_DESC() const
{
	return m_desc;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_DEPTH_STENCIL_STATE_INL_HPP
