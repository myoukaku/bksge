/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	ToD3D12TypeEnum 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D12_DETAIL_INL_TYPE_ENUM_INL_HPP
#define BKSGE_RENDER_D3D12_DETAIL_INL_TYPE_ENUM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D12_RENDERER

#include <bksge/render/d3d12/detail/type_enum.hpp>
#include <bksge/render/d3d_common/dxgi.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d12
{

BKSGE_INLINE ::DXGI_FORMAT
ToD3D12TypeEnum(bksge::TypeEnum type)
{
	static std::unordered_map<bksge::TypeEnum, ::DXGI_FORMAT> const m =
	{
		{bksge::TypeEnum::kSInt8,  DXGI_FORMAT_R8_SINT},
		{bksge::TypeEnum::kUInt8,  DXGI_FORMAT_R8_UINT},
		{bksge::TypeEnum::kSInt16, DXGI_FORMAT_R16_SINT},
		{bksge::TypeEnum::kUInt16, DXGI_FORMAT_R16_UINT},
		{bksge::TypeEnum::kSInt32, DXGI_FORMAT_R32_SINT},
		{bksge::TypeEnum::kUInt32, DXGI_FORMAT_R32_UINT},
		{bksge::TypeEnum::kFloat,  DXGI_FORMAT_R32_FLOAT},
	};

	return m.at(type);
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_TYPE_ENUM_INL_HPP
