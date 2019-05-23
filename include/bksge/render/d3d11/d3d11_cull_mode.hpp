/**
 *	@file	d3d11_cull_mode.hpp
 *
 *	@brief	ToD3D11CullMode 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_CULL_MODE_HPP
#define BKSGE_RENDER_D3D11_D3D11_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

::D3D11_CULL_MODE ToD3D11CullMode(CullMode cull_mode);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_cull_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_CULL_MODE_HPP
