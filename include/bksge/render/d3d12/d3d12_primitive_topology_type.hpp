/**
 *	@file	d3d12_primitive_topology_type.hpp
 *
 *	@brief	ToD3D12PrimitiveTopologyType 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_PRIMITIVE_TOPOLOGY_TYPE_HPP
#define BKSGE_RENDER_D3D12_D3D12_PRIMITIVE_TOPOLOGY_TYPE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/d3d_common/d3d12.hpp>

namespace bksge
{

namespace render
{

::D3D12_PRIMITIVE_TOPOLOGY_TYPE ToD3D12PrimitiveTopologyType(Primitive primitive);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_primitive_topology_type_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_PRIMITIVE_TOPOLOGY_TYPE_HPP
