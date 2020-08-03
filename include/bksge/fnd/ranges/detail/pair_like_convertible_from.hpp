/**
 *	@file	pair_like_convertible_from.hpp
 *
 *	@brief	pair_like_convertible_from の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP
#define BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/detail/pair_like.hpp>
#include <bksge/fnd/ranges/detail/convertible_to_non_slicing.hpp>
#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename V>
concept pair_like_convertible_from =
	!ranges::range<T> &&
	ranges::detail::pair_like<T> &&
	bksge::constructible_from<T, U, V> &&
	ranges::detail::convertible_to_non_slicing<U, bksge::tuple_element_t<0, T>> &&
	bksge::convertible_to<V, bksge::tuple_element_t<1, T>>;

#else

template <typename T, typename U, typename V>
using pair_like_convertible_from = bksge::conjunction<
	bksge::negation<ranges::range<T>>,
	ranges::detail::pair_like<T>,
	bksge::constructible_from<T, U, V>,
	ranges::detail::convertible_to_non_slicing<U, bksge::tuple_element_t<0, T>>,
	bksge::convertible_to<V, bksge::tuple_element_t<1, T>>
>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_CONVERTIBLE_FROM_HPP
