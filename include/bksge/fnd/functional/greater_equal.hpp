﻿/**
 *	@file	greater_equal.hpp
 *
 *	@brief	greater_equal クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_GREATER_EQUAL_HPP
#define BKSGE_FND_FUNCTIONAL_GREATER_EQUAL_HPP

#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/functional/detail/less_builtin_ptr_cmp.hpp>
#include <bksge/fnd/concepts/totally_ordered_with.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

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

namespace ranges
{

/**
 *	@brief	ranges::greater_equal
 */
struct greater_equal
{
	template <typename T, typename U
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::totally_ordered_with<T, U>::value ||
			detail::less_builtin_ptr_cmp<U, T>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires
		bksge::totally_ordered_with<T, U> ||
		detail::less_builtin_ptr_cmp<T, U>
#endif
	BKSGE_CONSTEXPR bool operator()(T&& t, U&& u) const
		BKSGE_NOEXCEPT_IF_EXPR(bksge::declval<T>() < bksge::declval<U>())
	{
		return !bksge::ranges::less{}(bksge::forward<T>(t), bksge::forward<U>(u));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_GREATER_EQUAL_HPP
