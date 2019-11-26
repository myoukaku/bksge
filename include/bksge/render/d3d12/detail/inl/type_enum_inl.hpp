/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	TypeEnum の実装
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

namespace bksge
{

namespace render
{

namespace d3d12
{

namespace detail
{

inline ::DXGI_FORMAT
ToD3D12TypeEnum(bksge::TypeEnum type)
{
	switch (type)
	{
	case bksge::TypeEnum::kSInt8:  return DXGI_FORMAT_R8_SINT;
	case bksge::TypeEnum::kUInt8:  return DXGI_FORMAT_R8_UINT;
	case bksge::TypeEnum::kSInt16: return DXGI_FORMAT_R16_SINT;
	case bksge::TypeEnum::kUInt16: return DXGI_FORMAT_R16_UINT;
	case bksge::TypeEnum::kSInt32: return DXGI_FORMAT_R32_SINT;
	case bksge::TypeEnum::kUInt32: return DXGI_FORMAT_R32_UINT;
	case bksge::TypeEnum::kFloat:  return DXGI_FORMAT_R32_FLOAT;
	}
	return DXGI_FORMAT_UNKNOWN;
}

}	// namespace detail

BKSGE_INLINE
TypeEnum::TypeEnum(bksge::TypeEnum type_enum)
	: m_type_enum(detail::ToD3D12TypeEnum(type_enum))
{}

BKSGE_INLINE
TypeEnum::operator DXGI_FORMAT() const
{
	return m_type_enum;
}

}	// namespace d3d12

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_D3D12_RENDERER

#endif // BKSGE_RENDER_D3D12_DETAIL_INL_TYPE_ENUM_INL_HPP
