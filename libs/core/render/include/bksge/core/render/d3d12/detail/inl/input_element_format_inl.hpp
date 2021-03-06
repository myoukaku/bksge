﻿/**
 *	@file	input_element_format_inl.hpp
 *
 *	@brief	ToD3D12InputElementFormat 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D12_DETAIL_INL_INPUT_ELEMENT_FORMAT_INL_HPP
#define BKSGE_CORE_RENDER_D3D12_DETAIL_INL_INPUT_ELEMENT_FORMAT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#include <bksge/core/render/d3d12/detail/input_element_format.hpp>
#include <bksge/core/render/d3d_common/dxgi.hpp>
#include <bksge/core/render/detail/type_enum.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE ::DXGI_FORMAT
ToD3D12InputElementFormat(bksge::TypeEnum type, bksge::size_t count)
{
	BKSGE_ASSERT(1u <= count && count <= 4u);
	static const ::DXGI_FORMAT format_tbl[][4] =
	{
		{
			DXGI_FORMAT_R8_SINT,
			DXGI_FORMAT_R8G8_SINT,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_R8G8B8A8_SINT,
		},
		{
			DXGI_FORMAT_R8_UINT,
			DXGI_FORMAT_R8G8_UINT,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_R8G8B8A8_UINT,
		},
		{
			DXGI_FORMAT_R16_SINT,
			DXGI_FORMAT_R16G16_SINT,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_R16G16B16A16_SINT,
		},
		{
			DXGI_FORMAT_R16_UINT,
			DXGI_FORMAT_R16G16_UINT,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_R16G16B16A16_UINT,
		},
		{
			DXGI_FORMAT_R32_SINT,
			DXGI_FORMAT_R32G32_SINT,
			DXGI_FORMAT_R32G32B32_SINT,
			DXGI_FORMAT_R32G32B32A32_SINT,
		},
		{
			DXGI_FORMAT_R32_UINT,
			DXGI_FORMAT_R32G32_UINT,
			DXGI_FORMAT_R32G32B32_UINT,
			DXGI_FORMAT_R32G32B32A32_UINT,
		},
		{
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_R32G32_FLOAT,
			DXGI_FORMAT_R32G32B32_FLOAT,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
		},
	};

	return format_tbl[static_cast<int>(type)][count - 1];
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_CORE_RENDER_D3D12_DETAIL_INL_INPUT_ELEMENT_FORMAT_INL_HPP
