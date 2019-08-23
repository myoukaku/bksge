/**
 *	@file	primitive_topology_type_inl.hpp
 *
 *	@brief	ToD3D12PrimitiveTopologyType 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/primitive_topology_type.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE ::D3D12_PRIMITIVE_TOPOLOGY_TYPE
ToD3D12PrimitiveTopologyType(bksge::Primitive primitive)
{
	static std::unordered_map<bksge::Primitive, ::D3D12_PRIMITIVE_TOPOLOGY_TYPE> const m =
	{
		{ bksge::Primitive::kPoints,    D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT },
		{ bksge::Primitive::kLines,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE },
		{ bksge::Primitive::kTriangles, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE },
	};

	return m.at(primitive);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP
