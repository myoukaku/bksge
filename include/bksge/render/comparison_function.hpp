/**
 *	@file	comparison_function.hpp
 *
 *	@brief	ComparisonFunction の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_COMPARISON_FUNCTION_HPP
#define BKSGE_RENDER_COMPARISON_FUNCTION_HPP

#include <bksge/render/fwd/comparison_function_fwd.hpp>
#include <cstdint>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	比較関数
 */
enum class ComparisonFunction : std::uint32_t
{
	kNever,
	kLess,
	kEqual,
	kLessEqual,
	kGreater,
	kNotEqual,
	kGreaterEqual,
	kAlways,
};

/**
 *	@brief	文字列への変換
 */
std::string to_string(ComparisonFunction const& comparison_function);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, ComparisonFunction const& rhs)
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
struct hash<bksge::render::ComparisonFunction>
{
	std::size_t operator()(bksge::render::ComparisonFunction const& arg) const
	{
		using underlying_type =
			typename std::underlying_type<bksge::render::ComparisonFunction>::type;
		return std::hash<underlying_type>{}(static_cast<underlying_type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_STD_VER <= 11

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/inl/comparison_function_inl.hpp>
#endif

#endif // BKSGE_RENDER_COMPARISON_FUNCTION_HPP
