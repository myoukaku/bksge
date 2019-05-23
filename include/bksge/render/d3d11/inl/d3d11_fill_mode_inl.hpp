/**
 *	@file	d3d11_fill_mode_inl.hpp
 *
 *	@brief	ToD3D11FillMode 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_FILL_MODE_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_FILL_MODE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_fill_mode.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>
#include <bksge/render/fill_mode.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE ::D3D11_FILL_MODE
ToD3D11FillMode(FillMode fill_mode)
{
	static std::unordered_map<FillMode, ::D3D11_FILL_MODE> const m =
	{
		{ FillMode::kSolid,     D3D11_FILL_SOLID },
		{ FillMode::kWireframe, D3D11_FILL_WIREFRAME },
	};

	return m.at(fill_mode);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_FILL_MODE_INL_HPP
