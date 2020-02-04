/**
 *	@file	border_color.hpp
 *
 *	@brief	BorderColor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_BORDER_COLOR_HPP
#define BKSGE_CORE_RENDER_BORDER_COLOR_HPP

#include <bksge/core/render/fwd/border_color_fwd.hpp>
#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	AddressMode が kBorder のときに塗りつぶす色
 */
enum class BorderColor
{
	kTransparentBlack,
	kOpaqueBlack,
	kOpaqueWhite,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(BorderColor const& border_color);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, BorderColor const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::BorderColor>
{
	std::size_t operator()(bksge::render::BorderColor const& arg) const
	{
		using underlying_type = typename std::underlying_type<bksge::render::BorderColor>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/border_color_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_BORDER_COLOR_HPP
