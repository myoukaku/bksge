/**
 *	@file	d3d12_primitive.hpp
 *
 *	@brief	ToD3D12Primitive 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_D3D12_PRIMITIVE_HPP
#define BKSGE_RENDER_D3D12_D3D12_PRIMITIVE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/d3d12/d3d12.hpp>

namespace bksge
{

namespace render
{

::D3D12_PRIMITIVE_TOPOLOGY ToD3D12Primitive(Primitive primitive);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/inl/d3d12_primitive_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_D3D12_PRIMITIVE_HPP
