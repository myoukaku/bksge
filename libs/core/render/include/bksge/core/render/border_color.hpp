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
#include <bksge/fnd/string/string.hpp>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	AddressMode が kBorder のときに塗りつぶす色
 */
enum class BorderColor : bksge::uint32_t
{
	kTransparentBlack,
	kOpaqueBlack,
	kOpaqueWhite,
};

/**
 *	@brief	文字列への変換
 */
bksge::string to_string(BorderColor const& border_color);

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

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/border_color_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_BORDER_COLOR_HPP
