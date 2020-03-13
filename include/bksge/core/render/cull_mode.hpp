/**
 *	@file	cull_mode.hpp
 *
 *	@brief	CullMode の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_CULL_MODE_HPP
#define BKSGE_CORE_RENDER_CULL_MODE_HPP

#include <bksge/core/render/fwd/cull_mode_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	ポリゴンのカリングモード
 */
enum class CullMode : bksge::uint32_t
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

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <cstddef>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::CullMode>
{
	std::size_t operator()(bksge::render::CullMode const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::CullMode>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/cull_mode_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_CULL_MODE_HPP
