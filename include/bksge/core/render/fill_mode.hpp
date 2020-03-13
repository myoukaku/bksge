/**
 *	@file	fill_mode.hpp
 *
 *	@brief	FillMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_FILL_MODE_HPP
#define BKSGE_CORE_RENDER_FILL_MODE_HPP

#include <bksge/core/render/fwd/fill_mode_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンの塗りつぶしモード
 */
enum class FillMode : bksge::uint32_t
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

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <cstddef>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::FillMode>
{
	std::size_t operator()(bksge::render::FillMode const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::FillMode>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/fill_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_FILL_MODE_HPP
