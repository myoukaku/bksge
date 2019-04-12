﻿/**
 *	@file	d3d11_format_inl.hpp
 *
 *	@brief	ToD3D11Format の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_INL_D3D11_FORMAT_INL_HPP
#define BKSGE_RENDER_D3D11_INL_D3D11_FORMAT_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/d3d11_format.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
DXGI_FORMAT ToD3D11Format(TypeEnum type)
{
	static std::unordered_map<TypeEnum, DXGI_FORMAT> const m =
	{
		{ TypeEnum::kByte,				DXGI_FORMAT_R8_SINT },
		{ TypeEnum::kUnsignedByte,		DXGI_FORMAT_R8_UINT },
		{ TypeEnum::kShort,				DXGI_FORMAT_R16_SINT },
		{ TypeEnum::kUnsignedShort,		DXGI_FORMAT_R16_UINT },
		{ TypeEnum::kInt,				DXGI_FORMAT_R32_SINT },
		{ TypeEnum::kUnsignedInt,		DXGI_FORMAT_R32_UINT },
		{ TypeEnum::kFloat,				DXGI_FORMAT_R32_FLOAT },
	};

	return m.at(type);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_INL_D3D11_FORMAT_INL_HPP