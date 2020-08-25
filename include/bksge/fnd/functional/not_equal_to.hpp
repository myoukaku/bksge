/**
 *	@file	not_equal_to.hpp
 *
 *	@brief	not_equal_to クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_NOT_EQUAL_TO_HPP
#define BKSGE_FND_FUNCTIONAL_NOT_EQUAL_TO_HPP

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	非等値比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct not_equal_to
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs != rhs;
	}
};

/**
 *	@brief	not_equal_to のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct not_equal_to<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	->decltype(bksge::forward<T>(lhs) != bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) != bksge::forward<U>(rhs);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_NOT_EQUAL_TO_HPP
