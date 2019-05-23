/**
 *	@file	d3d11_cull_mode_inl.hpp
 *
 *	@brief	ToD3D11CullMode 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_CULL_MODE_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_CULL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_cull_mode.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/cull_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE ::D3D11_CULL_MODE
ToD3D11CullMode(CullMode cull_mode)
{
	static std::unordered_map<CullMode, ::D3D11_CULL_MODE> const m =
	{
		{ CullMode::kNone,   D3D11_CULL_NONE },
		{ CullMode::kFront,  D3D11_CULL_FRONT },
		{ CullMode::kBack,   D3D11_CULL_BACK },
	};

	return m.at(cull_mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_CULL_MODE_INL_HPP
