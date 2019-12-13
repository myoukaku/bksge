/**
 *	@file	depth_stencil_state.hpp
 *
 *	@brief	DepthStencilState クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_STENCIL_STATE_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_STENCIL_STATE_HPP

#include <bksge/core/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

class DepthStencilState
{
public:
	DepthStencilState();

	operator ::D3D12_DEPTH_STENCIL_DESC() const;

private:
	::D3D12_DEPTH_STENCIL_DESC	m_desc;
};

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/depth_stencil_state_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_DEPTH_STENCIL_STATE_HPP
