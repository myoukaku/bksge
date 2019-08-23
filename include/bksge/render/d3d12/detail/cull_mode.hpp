/**
 *	@file	cull_mode.hpp
 *
 *	@brief	ToD3D12CullMode 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_CULL_MODE_HPP
#define BKSGE_RENDER_D3D12_DETAIL_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

::D3D12_CULL_MODE ToD3D12CullMode(bksge::CullMode cull_mode);

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_CULL_MODE_HPP
