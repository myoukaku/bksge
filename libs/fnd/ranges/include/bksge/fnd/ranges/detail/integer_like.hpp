/**
 *	@file	integer_like.hpp
 *
 *	@brief	integer_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_INTEGER_LIKE_HPP
#define BKSGE_FND_RANGES_DETAIL_INTEGER_LIKE_HPP

#include <bksge/fnd/ranges/detail/integral_nonbool.hpp>
#include <bksge/fnd/ranges/detail/max_diff_type.hpp>
#include <bksge/fnd/ranges/detail/max_size_type.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept integer_like =
	detail::integral_nonbool<T> ||
	bksge::same_as<T, detail::max_diff_type> ||
	bksge::same_as<T, detail::max_size_type>;

template <typename T>
concept not_integer_like = !integer_like<T>;

template <typename T>
using is_integer_like = bksge::bool_constant<integer_like<T>>;

#else

template <typename T>
using integer_like = bksge::disjunction<
	detail::integral_nonbool<T>,
	bksge::same_as<T, detail::max_diff_type>,
	bksge::same_as<T, detail::max_size_type>
>;

template <typename T>
using not_integer_like = bksge::negation<integer_like<T>>;

template <typename T>
using is_integer_like = integer_like<T>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_INTEGER_LIKE_HPP
