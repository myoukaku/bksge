/**
 *	@file	d3d11_primitive_inl.hpp
 *
 *	@brief	ToD3D11Primitive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_PRIMITIVE_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_PRIMITIVE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_primitive.hpp>
#include <bksge/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
D3D11_PRIMITIVE_TOPOLOGY
ToD3D11Primitive(Primitive primitive)
{
	static std::unordered_map<Primitive, D3D11_PRIMITIVE_TOPOLOGY> const m =
	{
		{ Primitive::kPoints,    D3D11_PRIMITIVE_TOPOLOGY_POINTLIST },
		{ Primitive::kLines,	 D3D11_PRIMITIVE_TOPOLOGY_LINELIST },
		{ Primitive::kTriangles, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST },
	};

	return m.at(primitive);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_PRIMITIVE_INL_HPP
