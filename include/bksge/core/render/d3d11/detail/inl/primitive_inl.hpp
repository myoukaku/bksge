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
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/primitive.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_PRIMITIVE_TOPOLOGY
ToD3D11Primitive(bksge::Primitive primitive)
{
	switch (primitive)
	{
	case bksge::Primitive::kPoints:    return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case bksge::Primitive::kLines:	   return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case bksge::Primitive::kTriangles: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
	return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}

}	// namespace detail

BKSGE_INLINE
Primitive::Primitive(bksge::Primitive primitive)
	: m_primitive(detail::ToD3D11Primitive(primitive))
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
