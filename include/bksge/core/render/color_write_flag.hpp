/**
 *	@file	color_write_flag.hpp
 *
 *	@brief	ColorWriteFlag の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_COLOR_WRITE_FLAG_HPP
#define BKSGE_CORE_RENDER_COLOR_WRITE_FLAG_HPP

#include <bksge/core/render/fwd/color_write_flag_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
enum class ColorWriteFlag : bksge::uint32_t
{
	kNone    = 0,

	kRed   = (1 << 0),
	kGreen = (1 << 1),
	kBlue  = (1 << 2),
	kAlpha = (1 << 3),

	kAll = kRed | kGreen | kBlue | kAlpha,
};

BKSGE_CONSTEXPR ColorWriteFlag
operator|(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR ColorWriteFlag
operator&(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR ColorWriteFlag
operator^(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ColorWriteFlag&
operator|=(ColorWriteFlag& lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ColorWriteFlag&
operator&=(ColorWriteFlag& lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CXX14_CONSTEXPR ColorWriteFlag&
operator^=(ColorWriteFlag& lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

BKSGE_CONSTEXPR bool
Test(ColorWriteFlag lhs, ColorWriteFlag rhs) BKSGE_NOEXCEPT;

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(ColorWriteFlag const& color_write_flag);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(bksge::basic_ostream<CharT, Traits>& os, ColorWriteFlag rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#include <bksge/core/render/inl/color_write_flag_inl.hpp>

#endif // BKSGE_CORE_RENDER_COLOR_WRITE_FLAG_HPP
