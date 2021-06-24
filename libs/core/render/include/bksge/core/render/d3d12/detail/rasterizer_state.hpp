/**
 *	@file	rasterizer_state.hpp
 *
 *	@brief	RasterizerState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_RASTERIZER_STATE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_RASTERIZER_STATE_HPP

#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/fwd/rasterizer_state_fwd.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class RasterizerState
{
public:
	explicit RasterizerState(bksge::RasterizerState const& state);

	operator ::D3D12_RASTERIZER_DESC() const;

private:
	::D3D12_RASTERIZER_DESC	m_desc;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/rasterizer_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_RASTERIZER_STATE_HPP
