/**
 *	@file	dxgi_format_inl.hpp
 *
 *	@brief	DXGIFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DXGI_INL_DXGI_FORMAT_INL_HPP
#define BKSGE_CORE_RENDER_DXGI_INL_DXGI_FORMAT_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_DXGI

#include <bksge/core/render/dxgi/dxgi_format.hpp>

namespace bksge
{

namespace render
{

namespace detail
{

inline ::DXGI_FORMAT
ToDXGIFormat(bksge::TextureFormat format)
{
	switch (format)
	{
	case bksge::TextureFormat::kUndefined:			return DXGI_FORMAT_UNKNOWN;
	case bksge::TextureFormat::kR_U8:				return DXGI_FORMAT_R8_UINT;
	case bksge::TextureFormat::kR_S8:				return DXGI_FORMAT_R8_SINT;
	case bksge::TextureFormat::kR_U8_NORM:			return DXGI_FORMAT_R8_UNORM;
	case bksge::TextureFormat::kR_S8_NORM:			return DXGI_FORMAT_R8_SNORM;
	case bksge::TextureFormat::kR_U16:				return DXGI_FORMAT_R16_UINT;
	case bksge::TextureFormat::kR_S16:				return DXGI_FORMAT_R16_SINT;
	case bksge::TextureFormat::kR_U16_NORM:			return DXGI_FORMAT_R16_UNORM;
	case bksge::TextureFormat::kR_S16_NORM:			return DXGI_FORMAT_R16_SNORM;
	case bksge::TextureFormat::kR_F16:				return DXGI_FORMAT_R16_FLOAT;
	case bksge::TextureFormat::kR_U32:				return DXGI_FORMAT_R32_UINT;
	case bksge::TextureFormat::kR_S32:				return DXGI_FORMAT_R32_SINT;
	case bksge::TextureFormat::kR_F32:				return DXGI_FORMAT_R32_FLOAT;
	case bksge::TextureFormat::kRG_U8:				return DXGI_FORMAT_R8G8_UINT;
	case bksge::TextureFormat::kRG_S8:				return DXGI_FORMAT_R8G8_SINT;
	case bksge::TextureFormat::kRG_U8_NORM:			return DXGI_FORMAT_R8G8_UNORM;
	case bksge::TextureFormat::kRG_S8_NORM:			return DXGI_FORMAT_R8G8_SNORM;
	case bksge::TextureFormat::kRG_U16:				return DXGI_FORMAT_R16G16_UINT;
	case bksge::TextureFormat::kRG_S16:				return DXGI_FORMAT_R16G16_SINT;
	case bksge::TextureFormat::kRG_U16_NORM:		return DXGI_FORMAT_R16G16_UNORM;
	case bksge::TextureFormat::kRG_S16_NORM:		return DXGI_FORMAT_R16G16_SNORM;
	case bksge::TextureFormat::kRG_F16:				return DXGI_FORMAT_R16G16_FLOAT;
	case bksge::TextureFormat::kRG_U32:				return DXGI_FORMAT_R32G32_UINT;
	case bksge::TextureFormat::kRG_S32:				return DXGI_FORMAT_R32G32_SINT;
	case bksge::TextureFormat::kRG_F32:				return DXGI_FORMAT_R32G32_FLOAT;
	case bksge::TextureFormat::kRGBA_U8:			return DXGI_FORMAT_R8G8B8A8_UINT;
	case bksge::TextureFormat::kRGBA_S8:			return DXGI_FORMAT_R8G8B8A8_SINT;
	case bksge::TextureFormat::kRGBA_U8_NORM:		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case bksge::TextureFormat::kRGBA_S8_NORM:		return DXGI_FORMAT_R8G8B8A8_SNORM;
	case bksge::TextureFormat::kRGBA_U16:			return DXGI_FORMAT_R16G16B16A16_UINT;
	case bksge::TextureFormat::kRGBA_S16:			return DXGI_FORMAT_R16G16B16A16_SINT;
	case bksge::TextureFormat::kRGBA_U16_NORM:		return DXGI_FORMAT_R16G16B16A16_UNORM;
	case bksge::TextureFormat::kRGBA_S16_NORM:		return DXGI_FORMAT_R16G16B16A16_SNORM;
	case bksge::TextureFormat::kRGBA_F16:			return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case bksge::TextureFormat::kRGBA_U32:			return DXGI_FORMAT_R32G32B32A32_UINT;
	case bksge::TextureFormat::kRGBA_S32:			return DXGI_FORMAT_R32G32B32A32_SINT;
	case bksge::TextureFormat::kRGBA_F32:			return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case bksge::TextureFormat::kDepth24_Stencil8:	return DXGI_FORMAT_D24_UNORM_S8_UINT;
	case bksge::TextureFormat::kBC1:				return DXGI_FORMAT_BC1_UNORM;
	case bksge::TextureFormat::kBC2:				return DXGI_FORMAT_BC2_UNORM;
	case bksge::TextureFormat::kBC3:				return DXGI_FORMAT_BC3_UNORM;
	case bksge::TextureFormat::kBC4:				return DXGI_FORMAT_BC4_UNORM;
	case bksge::TextureFormat::kBC5:				return DXGI_FORMAT_BC5_UNORM;
	case bksge::TextureFormat::kBC6H:				return DXGI_FORMAT_BC6H_UF16;
	case bksge::TextureFormat::kBC7:				return DXGI_FORMAT_BC7_UNORM;
	}
	return DXGI_FORMAT_UNKNOWN;
}

}	// namespace detail

BKSGE_INLINE
DXGIFormat::DXGIFormat(bksge::TextureFormat format)
	: m_format(detail::ToDXGIFormat(format))
{}

BKSGE_INLINE
DXGIFormat::operator ::DXGI_FORMAT() const
{
	return m_format;
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_DXGI

#endif // BKSGE_CORE_RENDER_DXGI_INL_DXGI_FORMAT_INL_HPP
