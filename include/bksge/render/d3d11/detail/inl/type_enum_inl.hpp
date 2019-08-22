/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	TypeEnum クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_D3D11_DETAIL_INL_TYPE_ENUM_INL_HPP
#define BKSGE_RENDER_D3D11_DETAIL_INL_TYPE_ENUM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_D3D11_RENDERER

#include <bksge/render/d3d11/detail/type_enum.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::DXGI_FORMAT
D3D11TypeEnum(bksge::TypeEnum type)
{
	static std::unordered_map<bksge::TypeEnum, ::DXGI_FORMAT> const m =
	{
		{ bksge::TypeEnum::kSInt8,	DXGI_FORMAT_R8_SINT },
		{ bksge::TypeEnum::kUInt8,	DXGI_FORMAT_R8_UINT },
		{ bksge::TypeEnum::kSInt16,	DXGI_FORMAT_R16_SINT },
		{ bksge::TypeEnum::kUInt16,	DXGI_FORMAT_R16_UINT },
		{ bksge::TypeEnum::kSInt32,	DXGI_FORMAT_R32_SINT },
		{ bksge::TypeEnum::kUInt32,	DXGI_FORMAT_R32_UINT },
		{ bksge::TypeEnum::kFloat,	DXGI_FORMAT_R32_FLOAT },
	};

	return m.at(type);
}

}	// namespace detail

BKSGE_INLINE
TypeEnum::TypeEnum(bksge::TypeEnum type)
	: m_type(detail::D3D11TypeEnum(type))
{}

BKSGE_INLINE
TypeEnum::operator ::DXGI_FORMAT() const
{
	return m_type;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_RENDER_D3D11_DETAIL_INL_TYPE_ENUM_INL_HPP
