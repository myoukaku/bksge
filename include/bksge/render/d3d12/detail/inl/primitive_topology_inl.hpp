﻿/**
 *	@file	primitive_topology_inl.hpp
 *
 *	@brief	PrimitiveTopology の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/primitive_topology.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/primitive.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::D3D12_PRIMITIVE_TOPOLOGY
ToD3D12PrimitiveTopology(bksge::Primitive primitive)
{
	switch (primitive)
	{
	case bksge::Primitive::kPoints:    return D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
	case bksge::Primitive::kLines:     return D3D_PRIMITIVE_TOPOLOGY_LINELIST;
	case bksge::Primitive::kTriangles: return D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	};
	return D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
}

}	// namespace detail

BKSGE_INLINE
PrimitiveTopology::PrimitiveTopology(bksge::Primitive primitive)
	: m_primitive_topology(detail::ToD3D12PrimitiveTopology(primitive))
{}

BKSGE_INLINE
PrimitiveTopology::operator D3D12_PRIMITIVE_TOPOLOGY() const
{
	return m_primitive_topology;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_INL_HPP
