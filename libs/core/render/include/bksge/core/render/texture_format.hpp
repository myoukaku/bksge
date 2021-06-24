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
#include <bksge/fnd/string/string.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ピクセルフォーマット
 */
enum class TextureFormat : bksge::uint32_t
{
	kUndefined = 0,

	kR_U8,
	kR_S8,
	kR_U8_NORM,
	kR_S8_NORM,
	kR_U16,
	kR_S16,
	kR_U16_NORM,
	kR_S16_NORM,
	kR_F16,
	kR_U32,
	kR_S32,
	kR_F32,

	kRG_U8,
	kRG_S8,
	kRG_U8_NORM,
	kRG_S8_NORM,
	kRG_U16,
	kRG_S16,
	kRG_U16_NORM,
	kRG_S16_NORM,
	kRG_F16,
	kRG_U32,
	kRG_S32,
	kRG_F32,

	kRGBA_U8,
	kRGBA_S8,
	kRGBA_U8_NORM,
	kRGBA_S8_NORM,
	kRGBA_U16,
	kRGBA_S16,
	kRGBA_U16_NORM,
	kRGBA_S16_NORM,
	kRGBA_F16,
	kRGBA_U32,
	kRGBA_S32,
	kRGBA_F32,

	kDepth24_Stencil8,

	kBC1,
	kBC2,
	kBC3,
	kBC4,
	kBC5,
	kBC6H,
	kBC7,
};

/**
 *	@brief	画像のバイト数を得る
 *
 *	@param	format	TextureFormat
 *	@param	width	横幅
 *	@param	height	高さ
 *
 *	@return	format,width,heightに設定された画像のバイト数
 */
bksge::size_t GetSizeInBytes(
	TextureFormat format,
	bksge::uint32_t width,
	bksge::uint32_t height);

/**
 *	@brief	画像の１行のバイト数を得る
 *
 *	@param	format	TextureFormat
 *	@param	width	横幅
 *
 *	@return	format,widthに設定された画像の１行のバイト数
 */
bksge::size_t GetStrideInBytes(
	TextureFormat format,
	bksge::uint32_t width);

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
bksge::string to_string(TextureFormat const& format);

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

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/texture_format_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_TEXTURE_FORMAT_HPP
