/**
 *	@file	input_element_format.hpp
 *
 *	@brief	ToD3D12InputElementFormat 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INPUT_ELEMENT_FORMAT_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INPUT_ELEMENT_FORMAT_HPP

#include <bksge/render/d3d_common/dxgi.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <cstddef>

namespace bksge
{

namespace render
{

namespace d3d12
{

::DXGI_FORMAT ToD3D12InputElementFormat(bksge::TypeEnum type, std::size_t count);

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/d3d12/detail/inl/input_element_format_inl.hpp>
#endif

#endif // BKSGE_RENDER_D3D12_DETAIL_INPUT_ELEMENT_FORMAT_HPP
