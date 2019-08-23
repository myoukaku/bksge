/**
 *	@file	primitive_inl.hpp
 *
 *	@brief	ToD3D12Primitive 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/primitive.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>
#include <bksge/render/primitive.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE ::D3D12_PRIMITIVE_TOPOLOGY
ToD3D12Primitive(bksge::Primitive primitive)
{
	static std::unordered_map<bksge::Primitive, ::D3D12_PRIMITIVE_TOPOLOGY> const m =
	{
		{ bksge::Primitive::kPoints,    D3D_PRIMITIVE_TOPOLOGY_POINTLIST },
		{ bksge::Primitive::kLines,     D3D_PRIMITIVE_TOPOLOGY_LINELIST },
		{ bksge::Primitive::kTriangles, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST },
	};

	return m.at(primitive);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_PRIMITIVE_INL_HPP
