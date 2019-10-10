/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_FILL_MODE_HPP
#define BKSGE_RENDER_FILL_MODE_HPP

#include <bksge/render/fwd/fill_mode_fwd.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンの塗りつぶしモード
 */
enum class FillMode : std::uint32_t
{
	kSolid,
	kWireframe,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(FillMode const& fill_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, FillMode const& rhs)
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
struct hash<bksge::render::FillMode>
{
	std::size_t operator()(bksge::render::FillMode const& arg) const
	{
		using underlying_type =
			typename std::underlying_type<bksge::render::FillMode>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_FILL_MODE_HPP
