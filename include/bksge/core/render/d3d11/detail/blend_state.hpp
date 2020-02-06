/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_BLEND_STATE_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_BLEND_STATE_HPP

#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/fwd/blend_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

class BlendState
{
public:
	explicit BlendState(bksge::BlendState const& blend_state);

	operator D3D11_BLEND_DESC_N() const;

private:
	D3D11_BLEND_DESC_N	m_desc;
};

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d11/detail/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_BLEND_STATE_HPP
