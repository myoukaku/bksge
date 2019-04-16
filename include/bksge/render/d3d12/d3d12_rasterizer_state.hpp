/**
 *	@file	d3d12_rasterizer_state.hpp
 *
 *	@brief	D3D12RasterizerState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_RASTERIZER_STATE_HPP
#define BKSGE_RENDER_D3D12_D3D12_RASTERIZER_STATE_HPP

#include <bksge/render/d3d12/d3d12.hpp>

namespace bksge
{

namespace render
{

class D3D12RasterizerState
{
public:
	D3D12RasterizerState();

	operator ::D3D12_RASTERIZER_DESC() const;

private:
	::D3D12_RASTERIZER_DESC	m_desc;
};

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_rasterizer_state_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_RASTERIZER_STATE_HPP
