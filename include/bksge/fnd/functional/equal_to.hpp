﻿/**
 *	@file	equal_to.hpp
 *
 *	@brief	equal_to クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_EQUAL_TO_HPP
#define BKSGE_FND_FUNCTIONAL_EQUAL_TO_HPP

#include <bksge/fnd/functional/detail/eq_builtin_ptr_cmp.hpp>
#include <bksge/fnd/concepts/equality_comparable_with.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	等値比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct equal_to
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs == rhs;
	}
};

/**
 *	@brief	equal_to のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct equal_to<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) == bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) == bksge::forward<U>(rhs);
	}
};

namespace ranges
{

/**
 *	@brief	ranges::equal_to
 */
struct equal_to
{
	template <typename T, typename U
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::equality_comparable_with<T, U>::value ||
			detail::eq_builtin_ptr_cmp<T, U>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires
		bksge::equality_comparable_with<T, U> ||
		detail::eq_builtin_ptr_cmp<T, U>
#endif
	BKSGE_CONSTEXPR bool operator()(T&& t, U&& u) const
		BKSGE_NOEXCEPT_IF_EXPR(bksge::declval<T>() == bksge::declval<U>())
	{
		return bksge::forward<T>(t) == bksge::forward<U>(u);
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_EQUAL_TO_HPP
