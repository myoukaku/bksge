/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_RASTERIZER_STATE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_RASTERIZER_STATE_HPP

#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/fwd/rasterizer_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

class RasterizerState
{
public:
	explicit RasterizerState(bksge::RasterizerState const& state);

	operator ::D3D11_RASTERIZER_DESC() const;

private:
	::D3D11_RASTERIZER_DESC	m_desc;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/rasterizer_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_RASTERIZER_STATE_HPP
