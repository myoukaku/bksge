/**
 *	@file	signed_integer_like.hpp
 *
 *	@brief	signed_integer_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_SIGNED_INTEGER_LIKE_HPP
#define BKSGE_FND_RANGES_DETAIL_SIGNED_INTEGER_LIKE_HPP

#include <bksge/fnd/ranges/detail/max_diff_type.hpp>
#include <bksge/fnd/concepts/signed_integral.hpp>
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
concept signed_integer_like =
	bksge::signed_integral<T> ||
	bksge::same_as<T, detail::max_diff_type>;

template <typename T>
concept not_signed_integer_like = !signed_integer_like<T>;

template <typename T>
using is_signed_integer_like = bksge::bool_constant<signed_integer_like<T>>;

#else

template <typename T>
using signed_integer_like = bksge::disjunction<
	bksge::signed_integral<T>,
	bksge::same_as<T, detail::max_diff_type>
>;

template <typename T>
using not_signed_integer_like = bksge::negation<signed_integer_like<T>>;

template <typename T>
using is_signed_integer_like = signed_integer_like<T>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_SIGNED_INTEGER_LIKE_HPP
