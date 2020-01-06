/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	TypeEnum クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_D3D11_DETAIL_INL_TYPE_ENUM_INL_HPP
#define BKSGE_CORE_RENDER_D3D11_DETAIL_INL_TYPE_ENUM_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#include <bksge/core/render/d3d11/detail/type_enum.hpp>
#include <bksge/core/render/detail/type_enum.hpp>

namespace bksge
{

namespace render
{

namespace d3d11
{

namespace detail
{

inline ::DXGI_FORMAT
ToD3D11TypeEnum(bksge::TypeEnum type)
{
	switch (type)
	{
	case bksge::TypeEnum::kSInt8:	return DXGI_FORMAT_R8_SINT;
	case bksge::TypeEnum::kUInt8:	return DXGI_FORMAT_R8_UINT;
	case bksge::TypeEnum::kSInt16:	return DXGI_FORMAT_R16_SINT;
	case bksge::TypeEnum::kUInt16:	return DXGI_FORMAT_R16_UINT;
	case bksge::TypeEnum::kSInt32:	return DXGI_FORMAT_R32_SINT;
	case bksge::TypeEnum::kUInt32:	return DXGI_FORMAT_R32_UINT;
	case bksge::TypeEnum::kFloat:	return DXGI_FORMAT_R32_FLOAT;
	}
	return DXGI_FORMAT_R8_SINT;
}

}	// namespace detail

BKSGE_INLINE
TypeEnum::TypeEnum(bksge::TypeEnum type)
	: m_type(detail::ToD3D11TypeEnum(type))
{}

BKSGE_INLINE
TypeEnum::operator ::DXGI_FORMAT() const
{
	return m_type;
}

}	// namespace d3d11

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_D3D11_RENDERER

#endif // BKSGE_CORE_RENDER_D3D11_DETAIL_INL_TYPE_ENUM_INL_HPP
