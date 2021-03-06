﻿/**
 *	@file	primitive_topology_type_inl.hpp
 *
 *	@brief	PrimitiveTopologyType の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/primitive_topology_type.hpp>
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

inline ::D3D12_PRIMITIVE_TOPOLOGY_TYPE
ToD3D12PrimitiveTopologyType(bksge::PrimitiveTopology primitive_topology)
{
	switch (primitive_topology)
	{
	case bksge::PrimitiveTopology::kPoints:    return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
	case bksge::PrimitiveTopology::kLines:     return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
	case bksge::PrimitiveTopology::kTriangles: return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	}
	return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
}

}	// namespace detail

BKSGE_INLINE
PrimitiveTopologyType::PrimitiveTopologyType(bksge::PrimitiveTopology primitive_topology)
	: m_primitive_topology_type(detail::ToD3D12PrimitiveTopologyType(primitive_topology))
{}

BKSGE_INLINE
PrimitiveTopologyType::operator D3D12_PRIMITIVE_TOPOLOGY_TYPE() const
{
	return m_primitive_topology_type;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP
