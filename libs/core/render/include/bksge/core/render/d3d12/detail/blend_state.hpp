/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_BLEND_STATE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_BLEND_STATE_HPP

#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/fwd/blend_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class BlendState
{
public:
	explicit BlendState(bksge::BlendState const& blend_state);

	operator ::D3D12_BLEND_DESC() const;

private:
	::D3D12_BLEND_DESC	m_desc;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_BLEND_STATE_HPP
