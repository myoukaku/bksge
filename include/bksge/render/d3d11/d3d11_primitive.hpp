/**
 *	@file	d3d11_primitive.hpp
 *
 *	@brief	ToD3D11Primitive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_PRIMITIVE_HPP
#define BKSGE_RENDER_D3D11_D3D11_PRIMITIVE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/d3d_common/d3d11.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	PrimitiveをD3D11のD3D11_PRIMITIVE_TOPOLOGYに変換
 */
::D3D11_PRIMITIVE_TOPOLOGY ToD3D11Primitive(Primitive primitive);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_primitive_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_PRIMITIVE_HPP
