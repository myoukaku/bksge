/**
 *	@file	d3d12_blend_state.hpp
 *
 *	@brief	D3D12BlendState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_BLEND_STATE_HPP
#define BKSGE_RENDER_D3D12_D3D12_BLEND_STATE_HPP

#include <bksge/render/d3d12/d3d12.hpp>

namespace bksge
{

namespace render
{

class D3D12BlendState
{
public:
	D3D12BlendState();

	operator ::D3D12_BLEND_DESC() const;

private:
	::D3D12_BLEND_DESC	m_desc;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_blend_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_BLEND_STATE_HPP
