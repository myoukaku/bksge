/**
 *	@file	texture_format_inl.hpp
 *
 *	@brief	TextureFormat の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_INL_TEXTURE_FORMAT_INL_HPP
#define BKSGE_CORE_RENDER_INL_TEXTURE_FORMAT_INL_HPP

#include <bksge/core/render/texture_format.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/cmath/round_up.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <cstdint>

namespace bksge
{

namespace render
{

inline std::size_t
GetBitsPerPixel(TextureFormat format)
{
	switch (format)
	{
	case bksge::TextureFormat::kUndefined:			return 0;
	case bksge::TextureFormat::kR_U8:				return  8 * 1;
	case bksge::TextureFormat::kR_S8:				return  8 * 1;
	case bksge::TextureFormat::kR_U8_NORM:			return  8 * 1;
	case bksge::TextureFormat::kR_S8_NORM:			return  8 * 1;
	case bksge::TextureFormat::kR_U16:				return 16 * 1;
	case bksge::TextureFormat::kR_S16:				return 16 * 1;
	case bksge::TextureFormat::kR_U16_NORM:			return 16 * 1;
	case bksge::TextureFormat::kR_S16_NORM:			return 16 * 1;
	case bksge::TextureFormat::kR_F16:				return 16 * 1;
	case bksge::TextureFormat::kR_U32:				return 32 * 1;
	case bksge::TextureFormat::kR_S32:				return 32 * 1;
	case bksge::TextureFormat::kR_F32:				return 32 * 1;
	case bksge::TextureFormat::kRG_U8:				return  8 * 2;
	case bksge::TextureFormat::kRG_S8:				return  8 * 2;
	case bksge::TextureFormat::kRG_U8_NORM:			return  8 * 2;
	case bksge::TextureFormat::kRG_S8_NORM:			return  8 * 2;
	case bksge::TextureFormat::kRG_U16:				return 16 * 2;
	case bksge::TextureFormat::kRG_S16:				return 16 * 2;
	case bksge::TextureFormat::kRG_U16_NORM:		return 16 * 2;
	case bksge::TextureFormat::kRG_S16_NORM:		return 16 * 2;
	case bksge::TextureFormat::kRG_F16:				return 16 * 2;
	case bksge::TextureFormat::kRG_U32:				return 32 * 2;
	case bksge::TextureFormat::kRG_S32:				return 32 * 2;
	case bksge::TextureFormat::kRG_F32:				return 32 * 2;
	case bksge::TextureFormat::kRGBA_U8:			return  8 * 4;
	case bksge::TextureFormat::kRGBA_S8:			return  8 * 4;
	case bksge::TextureFormat::kRGBA_U8_NORM:		return  8 * 4;
	case bksge::TextureFormat::kRGBA_S8_NORM:		return  8 * 4;
	case bksge::TextureFormat::kRGBA_U16:			return 16 * 4;
	case bksge::TextureFormat::kRGBA_S16:			return 16 * 4;
	case bksge::TextureFormat::kRGBA_U16_NORM:		return 16 * 4;
	case bksge::TextureFormat::kRGBA_S16_NORM:		return 16 * 4;
	case bksge::TextureFormat::kRGBA_F16:			return 16 * 4;
	case bksge::TextureFormat::kRGBA_U32:			return 32 * 4;
	case bksge::TextureFormat::kRGBA_S32:			return 32 * 4;
	case bksge::TextureFormat::kRGBA_F32:			return 32 * 4;
	case bksge::TextureFormat::kDepth24_Stencil8:	return 32;
	case bksge::TextureFormat::kBC1:				return 4;
	case bksge::TextureFormat::kBC2:				return 8;
	case bksge::TextureFormat::kBC3:				return 8;
	case bksge::TextureFormat::kBC4:				return 4;
	case bksge::TextureFormat::kBC5:				return 8;
	case bksge::TextureFormat::kBC6H:				return 8;
	case bksge::TextureFormat::kBC7:				return 8;
	}
	return 0;
}

BKSGE_INLINE std::size_t
GetSizeInBytes(
	TextureFormat format,
	std::uint32_t width,
	std::uint32_t height)
{
	return (width * height * GetBitsPerPixel(format)) / 8;
}

BKSGE_INLINE std::size_t
GetStrideInBytes(TextureFormat format, std::uint32_t width)
{
	return (width * GetBitsPerPixel(format)) / 8;
}

BKSGE_INLINE std::size_t
GetMipmappedSizeInBytes(
	TextureFormat format,
	std::uint32_t width,
	std::uint32_t height,
	std::size_t mipmap_level)
{
	if (format == TextureFormat::kUndefined ||
		width == 0 ||
		height == 0 ||
		mipmap_level == 0)
	{
		return 0;
	}

	auto w = width;
	auto h = height;
	std::size_t size = 0;

	while (mipmap_level != 0)
	{
		size += GetSizeInBytes(format, w, h);
		w /= 2;
		h /= 2;

		if (w == 0 && h == 0)
		{
			break;
		}

		w = (bksge::max)(w, 1u);
		h = (bksge::max)(h, 1u);
		--mipmap_level;
	}

	return size;
}

BKSGE_INLINE bksge::string
to_string(TextureFormat const& format)
{
#define BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(x)	case x: return #x

	switch (format)
	{
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kUndefined);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_U8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_S8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_U8_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_S8_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_U16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_S16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_U16_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_S16_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_F16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_U32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_S32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kR_F32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U8_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S8_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U16_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S16_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_F16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRG_F32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U8_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S8_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U16_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S16_NORM);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_F16);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_F32);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kDepth24_Stencil8);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC1);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC2);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC3);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC4);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC5);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC6H);
	BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP(TextureFormat::kBC7);
	}

	return "";

#undef BKSGE_CORE_RENDER_TEXTURE_FORMAT_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_TEXTURE_FORMAT_INL_HPP
