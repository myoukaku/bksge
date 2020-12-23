/**
 *	@file	texture_format.hpp
 *
 *	@brief	TextureFormat の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_TEXTURE_FORMAT_HPP
#define BKSGE_CORE_RENDER_TEXTURE_FORMAT_HPP

#include <bksge/core/render/fwd/texture_format_fwd.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

static bksge::uint32_t const kChannelCountMask    = 0xF0000000;
static bksge::uint32_t const kChannelCountShift   = 28;

static bksge::uint32_t const kPixelSwizzleMask    = 0x00FF0000;
static bksge::uint32_t const kPixelSwizzleShift   = 16;

static bksge::uint32_t const kBitsPerChannelMask  = 0x0000FF00;
static bksge::uint32_t const kBitsPerChannelShift = 8;

static bksge::uint32_t const kDataTypeMask        = 0x0000000F;
static bksge::uint32_t const kDataTypeShift       = 0;

/**
 *	@brief	チャンネルの型です
 */
enum class DataType
{
	kNone,
	kUnsigned,
	kSigned,
	kFloat,
	kCompressed,
};

/**
 *	@brief	ピクセルのスウィズルモードです
 */
enum class PixelSwizzle
{
	kNone,
	kR,
	kRG,
	kRGB,
	kBGR,
	kRGBA,
	kBGRA,
	kARGB,
	kABGR,
	kDxt1,
	kDxt3,
	kDxt5,
};

/**
 *	@brief	ピクセルのベースフォーマットです
 *
 *	ベースフォーマットとスウィズルモードを組み合わせてピクセルフォーマットを作成します。
 */
enum class PixelBaseFormat
{
#define BKSGE_MAKE_PIXEL_DATA_TYPE(bpc, type)	\
	(static_cast<bksge::uint32_t>(bpc) << kBitsPerChannelShift) |	\
	(static_cast<bksge::uint32_t>(DataType::type) << kDataTypeShift)

	kNone	= 0,
	kU8		= BKSGE_MAKE_PIXEL_DATA_TYPE(8,  kUnsigned),
	kS8		= BKSGE_MAKE_PIXEL_DATA_TYPE(8,  kSigned),
	kU16	= BKSGE_MAKE_PIXEL_DATA_TYPE(16, kUnsigned),
	kS16	= BKSGE_MAKE_PIXEL_DATA_TYPE(16, kSigned),
	kU32	= BKSGE_MAKE_PIXEL_DATA_TYPE(32, kUnsigned),
	kS32	= BKSGE_MAKE_PIXEL_DATA_TYPE(32, kSigned),
	kF32	= BKSGE_MAKE_PIXEL_DATA_TYPE(32, kFloat),
	kDxt1	= BKSGE_MAKE_PIXEL_DATA_TYPE(1,  kCompressed),
	kDxt35	= BKSGE_MAKE_PIXEL_DATA_TYPE(2,  kCompressed),

#undef BKSGE_MAKE_PIXEL_DATA_TYPE
};

static bksge::uint32_t const kPixelBaseFormatMask = 0x0000FFFF;
static bksge::uint32_t const kPixelBaseFormatShift = 0;

/**
 *	@brief	ピクセルフォーマット
 *
 *	ビットごとの情報は以下のとおり
 *	 0- 3	１ピクセルのチャンネル数
 *	 4- 7	未使用
 *	 8-15	スウィズルの種類
 *	16-23	チャンネルあたりのビット数
 *	24-27	未使用
 *	28-31	データの型
 */
enum class TextureFormat
{
#define BKSGE_MAKE_TEXTURE_FORMAT(channels, swizzle, base)	\
	((static_cast<bksge::uint32_t>(channels) << kChannelCountShift)		 |	\
	(static_cast<bksge::uint32_t>(PixelSwizzle::swizzle) << kPixelSwizzleShift) |	\
	(static_cast<bksge::uint32_t>(PixelBaseFormat::base)))

	kNone		= 0,

	kR_U8		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kU8),
	kR_S8		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kS8),
	kR_U16		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kU16),
	kR_S16		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kS16),
	kR_U32		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kU32),
	kR_S32		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kS32),
	kR_F32		= BKSGE_MAKE_TEXTURE_FORMAT(1, kR, kF32),

	kRG_U8		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kU8),
	kRG_S8		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kS8),
	kRG_U16		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kU16),
	kRG_S16		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kS16),
	kRG_U32		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kU32),
	kRG_S32		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kS32),
	kRG_F32		= BKSGE_MAKE_TEXTURE_FORMAT(2, kRG, kF32),

	kRGB_U8		= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kU8),
	kRGB_S8		= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kS8),
	kRGB_U16	= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kU16),
	kRGB_S16	= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kS16),
	kRGB_U32	= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kU32),
	kRGB_S32	= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kS32),
	kRGB_F32	= BKSGE_MAKE_TEXTURE_FORMAT(3, kRGB, kF32),

	kBGR_U8		= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kU8),
	kBGR_S8		= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kS8),
	kBGR_U16	= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kU16),
	kBGR_S16	= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kS16),
	kBGR_U32	= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kU32),
	kBGR_S32	= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kS32),
	kBGR_F32	= BKSGE_MAKE_TEXTURE_FORMAT(3, kBGR, kF32),

	kRGBA_U8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kU8),
	kRGBA_S8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kS8),
	kRGBA_U16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kU16),
	kRGBA_S16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kS16),
	kRGBA_U32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kU32),
	kRGBA_S32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kS32),
	kRGBA_F32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kRGBA, kF32),

	kBGRA_U8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kU8),
	kBGRA_S8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kS8),
	kBGRA_U16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kU16),
	kBGRA_S16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kS16),
	kBGRA_U32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kU32),
	kBGRA_S32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kS32),
	kBGRA_F32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kBGRA, kF32),

	kARGB_U8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kU8),
	kARGB_S8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kS8),
	kARGB_U16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kU16),
	kARGB_S16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kS16),
	kARGB_U32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kU32),
	kARGB_S32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kS32),
	kARGB_F32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kARGB, kF32),

	kABGR_U8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kU8),
	kABGR_S8	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kS8),
	kABGR_U16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kU16),
	kABGR_S16	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kS16),
	kABGR_U32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kU32),
	kABGR_S32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kS32),
	kABGR_F32	= BKSGE_MAKE_TEXTURE_FORMAT(4, kABGR, kF32),

	kDxt1		= BKSGE_MAKE_TEXTURE_FORMAT(4, kDxt1, kDxt1),
	kDxt3		= BKSGE_MAKE_TEXTURE_FORMAT(4, kDxt3, kDxt35),
	kDxt5		= BKSGE_MAKE_TEXTURE_FORMAT(4, kDxt5, kDxt35),

#undef BKSGE_MAKE_TEXTURE_FORMAT
};

/**
 *	@brief	TextureFormatからPixelSwizzleを得る
 */
PixelSwizzle GetPixelSwizzle(TextureFormat format);

/**
 *	@brief	TextureFormatからPixelBaseFormatを得る
 */
PixelBaseFormat GetPixelBaseFormat(TextureFormat format);

/**
 *	@brief	TextureFormatからチャンネル数を得る
 */
bksge::size_t GetChannelCount(TextureFormat format);

/**
 *	@brief	TextureFormatから1チャンネルあたりのビット数を得る
 */
bksge::size_t GetBitsPerChannel(TextureFormat format);

/**
 *	@brief	TextureFormatからDXT圧縮されているかどうかを得る
 */
bool IsDxtCompressed(TextureFormat format);

/**
 *	@brief	TextureFormatから1ピクセルあたりのビット数を得る
 */
bksge::size_t GetBitsPerPixel(TextureFormat format);

/**
 *	@brief	画像のバイト数を得る
 *
 *	@param	format	TextureFormat
 *	@param	width	横幅
 *	@param	height	高さ
 *
 *	@return	format,width,heightに設定された画像のバイト数
 */
bksge::size_t GetSizeInBytes(TextureFormat format, bksge::uint32_t width, bksge::uint32_t height);

/**
 *	@brief	画像の１行のバイト数を得る
 *
 *	@param	format	TextureFormat
 *	@param	width	横幅
 *
 *	@return	format,widthに設定された画像の１行のバイト数
 */
bksge::size_t GetStrideInBytes(TextureFormat format, bksge::uint32_t width);

/**
 *	@brief	ミップマップレベルを考慮した画像のバイト数を得る
 *
 *	@param	format			TextureFormat
 *	@param	width			横幅
 *	@param	height			高さ
 *	@param	mipmap_level	ミップマップレベル
 *
 *	@return	format,width,height,mipmap_levelに設定された画像のバイト数
 */
bksge::size_t GetMipmappedSizeInBytes(
	TextureFormat format,
	bksge::uint32_t width,
	bksge::uint32_t height,
	bksge::size_t mipmap_level);

/**
 *	@brief	文字列への変換
 */
std::string to_string(TextureFormat const& format);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, TextureFormat const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::PixelSwizzle>
{
	bksge::size_t operator()(bksge::render::PixelSwizzle const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::PixelSwizzle>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

template<>
struct hash<bksge::render::PixelBaseFormat>
{
	bksge::size_t operator()(bksge::render::PixelBaseFormat const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::PixelBaseFormat>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

template<>
struct hash<bksge::render::TextureFormat>
{
	bksge::size_t operator()(bksge::render::TextureFormat const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::TextureFormat>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/texture_format_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_TEXTURE_FORMAT_HPP
