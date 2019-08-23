/**
 *	@file	type_enum.hpp
 *
 *	@brief	ToD3D12TypeEnum 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_TYPE_ENUM_HPP
#define BKSGE_RENDER_D3D12_DETAIL_TYPE_ENUM_HPP

#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/d3d_common/dxgi.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

::DXGI_FORMAT ToD3D12TypeEnum(bksge::TypeEnum type);

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/type_enum_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_TYPE_ENUM_HPP
