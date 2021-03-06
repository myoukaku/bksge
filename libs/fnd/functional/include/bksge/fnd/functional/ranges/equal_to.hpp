﻿/**
 *	@file	equal_to.hpp
 *
 *	@brief	ranges::equal_to クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_RANGES_EQUAL_TO_HPP
#define BKSGE_FND_FUNCTIONAL_RANGES_EQUAL_TO_HPP

#include <bksge/fnd/functional/detail/eq_builtin_ptr_cmp.hpp>
#include <bksge/fnd/concepts/equality_comparable_with.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

/**
 *	@brief	ranges::equal_to
 */
struct equal_to
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename T, typename U>
	requires
		bksge::equality_comparable_with<T, U> ||
		detail::eq_builtin_ptr_cmp<T, U>
#else
	template <typename T, typename U,
		typename = bksge::enable_if_t<
			bksge::equality_comparable_with<T, U>::value ||
			detail::eq_builtin_ptr_cmp<T, U>::value
		>
	>
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

#endif // BKSGE_FND_FUNCTIONAL_RANGES_EQUAL_TO_HPP
