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
#include <bksge/fnd/string/string.hpp>
#include <ostream>
#include <cstdint>

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
bksge::string to_string(ComparisonFunction const& comparison_function);

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

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/inl/comparison_function_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_COMPARISON_FUNCTION_HPP
