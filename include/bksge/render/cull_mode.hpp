/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_CULL_MODE_HPP
#define BKSGE_RENDER_CULL_MODE_HPP

#include <bksge/render/fwd/cull_mode_fwd.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンのカリングモード
 */
enum class CullMode : std::uint32_t
{
	kNone,
	kFront,
	kBack,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(CullMode const& cull_mode);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, CullMode const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_STD_VER <= 11

#include <functional>
#include <type_traits>

namespace std
{

template<>
struct hash<bksge::render::CullMode>
{
	std::size_t operator()(bksge::render::CullMode const& arg) const
	{
		using underlying_type =
			typename std::underlying_type<bksge::render::CullMode>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_STD_VER <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_RENDER_CULL_MODE_HPP
