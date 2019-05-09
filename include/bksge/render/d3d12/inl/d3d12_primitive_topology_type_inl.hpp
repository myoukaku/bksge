/**
 *	@file	d3d12_primitive_topology_type_inl.hpp
 *
 *	@brief	ToD3D12PrimitiveTopologyType 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_INL_D3D12_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP
#define BKSGE_RENDER_D3D12_INL_D3D12_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/d3d12_primitive_topology_type.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE ::D3D12_PRIMITIVE_TOPOLOGY_TYPE
ToD3D12PrimitiveTopologyType(Primitive primitive)
{
	static std::unordered_map<Primitive, ::D3D12_PRIMITIVE_TOPOLOGY_TYPE> const m =
	{
		{ Primitive::kPoints,    D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT },
		{ Primitive::kLines,     D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE },
		{ Primitive::kTriangles, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE },
	};

	return m.at(primitive);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_INL_D3D12_PRIMITIVE_TOPOLOGY_TYPE_INL_HPP
