/**
 *	@file	d3d11_format.hpp
 *
 *	@brief	ToD3D11Format の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_D3D11_FORMAT_HPP
#define BKSGE_RENDER_D3D11_D3D11_FORMAT_HPP

#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/d3d_common/dxgiformat.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief	TypeEnumをD3D11のDXGI_FORMATに変換
 */
::DXGI_FORMAT ToD3D11Format(TypeEnum type);

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d11/inl/d3d11_format_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D11_D3D11_FORMAT_HPP
