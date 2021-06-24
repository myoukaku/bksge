/**
 *	@file	primitive_topology_inl.hpp
 *
 *	@brief	PrimitiveTopology クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/primitive_topology.hpp>
#include <bksge/core/render/d3d_common/d3d11.hpp>
#include <bksge/core/render/primitive_topology.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::D3D11_PRIMITIVE_TOPOLOGY
ToD3D11PrimitiveTopology(bksge::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case bksge::PrimitiveTopology::kPoints:    return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case bksge::PrimitiveTopology::kLines:	   return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case bksge::PrimitiveTopology::kTriangles: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
	return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
}

}	// namespace detail

BKSGE_INLINE
PrimitiveTopology::PrimitiveTopology(bksge::PrimitiveTopology primitive_topology)
	: m_primitive_topology(detail::ToD3D11PrimitiveTopology(primitive_topology))
{}

BKSGE_INLINE
PrimitiveTopology::operator ::D3D11_PRIMITIVE_TOPOLOGY() const
{
	return m_primitive_topology;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
