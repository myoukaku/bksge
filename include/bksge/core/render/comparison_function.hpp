/**
 *	@file	comparison_function.hpp
 *
 *	@brief	ComparisonFunction の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_COMPARISON_FUNCTION_HPP
#define BKSGE_CORE_RENDER_COMPARISON_FUNCTION_HPP

#include <bksge/core/render/fwd/comparison_function_fwd.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <string>
#include <ostream>

namespace bksge
{

namespace render
{

/**
 *	@brief	比較関数
 */
enum class ComparisonFunction : bksge::uint32_t
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

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::ComparisonFunction>
{
	bksge::size_t operator()(bksge::render::ComparisonFunction const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::ComparisonFunction>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/comparison_function_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_COMPARISON_FUNCTION_HPP
