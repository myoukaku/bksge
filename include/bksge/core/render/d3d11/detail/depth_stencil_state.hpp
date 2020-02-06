/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_STATE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_STATE_HPP

#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/fwd/depth_state_fwd.hpp>
#include <bksge/core/render/fwd/stencil_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

class DepthStencilState
{
public:
	explicit DepthStencilState(
		bksge::DepthState const& depth_state,
		bksge::StencilState const& stencil_state);

	operator ::D3D11_DEPTH_STENCIL_DESC() const;

private:
	::D3D11_DEPTH_STENCIL_DESC	m_desc;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/depth_stencil_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_DEPTH_STENCIL_STATE_HPP
