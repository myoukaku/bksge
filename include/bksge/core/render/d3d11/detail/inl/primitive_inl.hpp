/**
 *	@file	primitive_inl.hpp
 *
 *	@brief	Primitive クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_PRIMITIVE_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_PRIMITIVE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/primitive.hpp>
#include <bksge/core/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_PRIMITIVE_TOPOLOGY
D3D11Primitive(bksge::Primitive primitive)
{
	static std::unordered_map<bksge::Primitive, ::D3D11_PRIMITIVE_TOPOLOGY> const m =
	{
		{ bksge::Primitive::kPoints,    D3D11_PRIMITIVE_TOPOLOGY_POINTLIST },
		{ bksge::Primitive::kLines,	    D3D11_PRIMITIVE_TOPOLOGY_LINELIST },
		{ bksge::Primitive::kTriangles, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST },
	};

	return m.at(primitive);
}

}	// namespace detail

BKSGE_INLINE
Primitive::Primitive(bksge::Primitive primitive)
	: m_primitive(detail::D3D11Primitive(primitive))
{}

BKSGE_INLINE
Primitive::operator ::D3D11_PRIMITIVE_TOPOLOGY() const
{
	return m_primitive;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_PRIMITIVE_INL_HPP
