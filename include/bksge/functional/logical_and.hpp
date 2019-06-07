/**
 *	@file	logical_and.hpp
 *
 *	@brief	logical_and クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FUNCTIONAL_LOGICAL_AND_HPP
#define BKSGE_FUNCTIONAL_LOGICAL_AND_HPP

#include <bksge/utility/forward.hpp>
#include <bksge/config.hpp>

namespace bksge
{

/**
 *	@brief	論理積(AND)を計算する関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct logical_and
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs && rhs;
	}
};

/**
 *	@brief	logical_and のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct logical_and<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) && bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) && bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FUNCTIONAL_LOGICAL_AND_HPP
