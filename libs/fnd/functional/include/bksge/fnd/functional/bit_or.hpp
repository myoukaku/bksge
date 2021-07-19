/**
 *	@file	bit_or.hpp
 *
 *	@brief	bit_or クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_BIT_OR_HPP
#define BKSGE_FND_FUNCTIONAL_BIT_OR_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_FUNCTIONAL_OPERATORS)

namespace bksge
{

using std::bit_or;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

/**
 *	@brief	ビットごとの論理和(OR)をとる関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct bit_or
{
	BKSGE_CONSTEXPR T operator()(T const& lhs, T const& rhs) const
	{
		return lhs | rhs;
	}
};

/**
 *	@brief	bit_or のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct bit_or<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(std::forward<T>(lhs) | std::forward<U>(rhs))
	{
		return std::forward<T>(lhs) | std::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_BIT_OR_HPP
