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
#include <bksge/fnd/config.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief
 */
enum class ColorWriteFlag : std::uint32_t
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
std::string to_string(ColorWriteFlag const& color_write_flag);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ColorWriteFlag rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::ColorWriteFlag>
{
	bksge::size_t operator()(bksge::render::ColorWriteFlag const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::ColorWriteFlag>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/core/render/inl/color_write_flag_inl.hpp>

#endif // BKSGE_CORE_RENDER_COLOR_WRITE_FLAG_HPP
