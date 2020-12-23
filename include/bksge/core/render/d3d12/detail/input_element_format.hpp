/**
 *	@file	input_element_format.hpp
 *
 *	@brief	ToD3D12InputElementFormat 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INPUT_ELEMENT_FORMAT_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INPUT_ELEMENT_FORMAT_HPP

#include <bksge/core/render/d3d_common/dxgi.hpp>
#include <bksge/core/render/detail/type_enum.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

::DXGI_FORMAT ToD3D12InputElementFormat(bksge::TypeEnum type, bksge::size_t count);

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/d3d12/detail/inl/input_element_format_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INPUT_ELEMENT_FORMAT_HPP
