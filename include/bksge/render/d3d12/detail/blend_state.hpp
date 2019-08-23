/**
 *	@file	blend_state.hpp
 *
 *	@brief	BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_BLEND_STATE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_BLEND_STATE_HPP

#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class BlendState
{
public:
	BlendState();

	operator ::D3D12_BLEND_DESC() const;

private:
	::D3D12_BLEND_DESC	m_desc;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/blend_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_BLEND_STATE_HPP
