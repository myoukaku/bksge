/**
 *	@file	greater_equal.hpp
 *
 *	@brief	greater_equal クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FUNCTIONAL_GREATER_EQUAL_HPP
#define BKSGE_FUNCTIONAL_GREATER_EQUAL_HPP

#include <bksge/utility/forward.hpp>
#include <bksge/config.hpp>

namespace bksge
{

/**
 *	@brief	左辺が右辺以上かの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct greater_equal
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs >= rhs;
	}
};

/**
 *	@brief	greater_equal のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct greater_equal<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) >= bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) >= bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FUNCTIONAL_GREATER_EQUAL_HPP
