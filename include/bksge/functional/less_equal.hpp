/**
 *	@file	less_equal.hpp
 *
 *	@brief	less_equal クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FUNCTIONAL_LESS_EQUAL_HPP
#define BKSGE_FUNCTIONAL_LESS_EQUAL_HPP

#include <bksge/utility/forward.hpp>
#include <bksge/config.hpp>

namespace bksge
{

/**
 *	@brief	左辺が右辺以下かの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct less_equal
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs <= rhs;
	}
};

/**
 *	@brief	less_equal のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct less_equal<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) <= bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) <= bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FUNCTIONAL_LESS_EQUAL_HPP
