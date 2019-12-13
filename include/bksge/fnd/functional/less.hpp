/**
 *	@file	less.hpp
 *
 *	@brief	less クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LESS_HPP
#define BKSGE_FND_FUNCTIONAL_LESS_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	左辺が右辺より小さいかの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct less
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs < rhs;
	}
};

/**
 *	@brief	less のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct less<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) < bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) < bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_LESS_HPP
