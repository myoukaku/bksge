/**
 *	@file	bit_or.hpp
 *
 *	@brief	bit_or クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_BIT_OR_HPP
#define BKSGE_FND_FUNCTIONAL_BIT_OR_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

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
	using result_type          = T;
	using first_argument_type  = T;
	using second_argument_type = T;

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
	-> decltype(bksge::forward<T>(lhs) | bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) | bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_BIT_OR_HPP
