/**
 *	@file	primitive_topology_inl.hpp
 *
 *	@brief	PrimitiveTopology の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/primitive_topology.hpp>
#include <bksge/core/render/d3d_common/d3d12.hpp>
#include <bksge/core/render/primitive_topology.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_PRIMITIVE_TOPOLOGY
ToD3D12PrimitiveTopology(bksge::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case bksge::PrimitiveTopology::kPoints:    return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
	case bksge::PrimitiveTopology::kLines:     return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	case bksge::PrimitiveTopology::kTriangles: return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
	return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
}

}	// namespace detail

BKSGE_INLINE
PrimitiveTopology::PrimitiveTopology(bksge::PrimitiveTopology primitive_topology)
	: m_primitive_topology(detail::ToD3D12PrimitiveTopology(primitive_topology))
{}

BKSGE_INLINE
PrimitiveTopology::operator D3D12_PRIMITIVE_TOPOLOGY() const
{
	return m_primitive_topology;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
