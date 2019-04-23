/**
 *	@file	d3d12_depth_stencil_state.hpp
 *
 *	@brief	D3D12DepthStencilState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_DEPTH_STENCIL_STATE_HPP
#define BKSGE_RENDER_D3D12_D3D12_DEPTH_STENCIL_STATE_HPP

#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

class D3D12DepthStencilState
{
public:
	D3D12DepthStencilState();

	operator ::D3D12_DEPTH_STENCIL_DESC() const;

private:
	::D3D12_DEPTH_STENCIL_DESC	m_desc;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_depth_stencil_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_DEPTH_STENCIL_STATE_HPP
