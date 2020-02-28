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
#include <bksge/fnd/cmath/round_up.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <string>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE PixelSwizzle
GetPixelSwizzle(TextureFormat format)
{
	return static_cast<PixelSwizzle>(
		(static_cast<std::uint32_t>(format) & kPixelSwizzleMask) >> kPixelSwizzleShift);
}

BKSGE_INLINE PixelBaseFormat
GetPixelBaseFormat(TextureFormat format)
{
	return static_cast<PixelBaseFormat>(
		(static_cast<std::uint32_t>(format) & kPixelBaseFormatMask) >> kPixelBaseFormatShift);
}

BKSGE_INLINE bksge::size_t
GetChannelCount(TextureFormat format)
{
	return (static_cast<std::uint32_t>(format) & kChannelCountMask) >> kChannelCountShift;
}

BKSGE_INLINE bksge::size_t
GetBitsPerChannel(TextureFormat format)
{
	return (static_cast<std::uint32_t>(format) & kBitsPerChannelMask) >> kBitsPerChannelShift;
}

BKSGE_INLINE bool
IsDxtCompressed(TextureFormat format)
{
	return
		format == TextureFormat::kDxt1 ||
		format == TextureFormat::kDxt3 ||
		format == TextureFormat::kDxt5;
}

BKSGE_INLINE bksge::size_t
GetBitsPerPixel(TextureFormat format)
{
	return GetChannelCount(format) * GetBitsPerChannel(format);
}

BKSGE_INLINE bksge::size_t
GetSizeInBytes(
	TextureFormat format,
	std::uint32_t width,
	std::uint32_t height)
{
	if (IsDxtCompressed(format))
	{
		width  = bksge::round_up(width, 4);
		height = bksge::round_up(height, 4);
	}

	return (width * height * GetBitsPerPixel(format)) / 8;
}

BKSGE_INLINE bksge::size_t
GetStrideInBytes(TextureFormat format, std::uint32_t width)
{
	if (IsDxtCompressed(format))
	{
		width  = bksge::round_up(width, 4);
	}

	return (width * GetBitsPerPixel(format)) / 8;
}

BKSGE_INLINE bksge::size_t
GetMipmappedSizeInBytes(
	TextureFormat format,
	std::uint32_t width,
	std::uint32_t height,
	bksge::size_t mipmap_level)
{
	if (format == TextureFormat::kNone ||
		width == 0 ||
		height == 0 ||
		mipmap_level == 0)
	{
		return 0;
	}

	auto w = width;
	auto h = height;
	bksge::size_t size = 0;

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

BKSGE_INLINE std::string
to_string(TextureFormat const& format)
{
#define BKSGE_MAKE_TEXTURE_FORMAT_KVP(x)	{ x, #x }

	static std::unordered_map<TextureFormat, std::string> const m =
	{
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kNone),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kR_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRG_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGB_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGR_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kRGBA_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kBGRA_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kARGB_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_U8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_S8),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_U16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_S16),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_U32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_S32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kABGR_F32),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kDxt1),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kDxt3),
		BKSGE_MAKE_TEXTURE_FORMAT_KVP(TextureFormat::kDxt5),
	};

	return m.at(format);

#undef BKSGE_MAKE_TEXTURE_FORMAT_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_INL_TEXTURE_FORMAT_INL_HPP
