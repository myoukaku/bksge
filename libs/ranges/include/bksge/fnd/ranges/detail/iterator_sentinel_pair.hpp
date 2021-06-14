/**
 *	@file	iterator_sentinel_pair.hpp
 *
 *	@brief	iterator_sentinel_pair の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_ITERATOR_SENTINEL_PAIR_HPP
#define BKSGE_FND_RANGES_DETAIL_ITERATOR_SENTINEL_PAIR_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/detail/pair_like.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
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

template <typename T>
concept iterator_sentinel_pair =
	!ranges::range<T> &&
	ranges::detail::pair_like<T> &&
	bksge::sentinel_for<bksge::tuple_element_t<1, T>, bksge::tuple_element_t<0, T>>;

#else

template <typename T>
using iterator_sentinel_pair = bksge::conjunction<
	bksge::negation<ranges::range<T>>,
	ranges::detail::pair_like<T>,
	bksge::sentinel_for<bksge::tuple_element_t<1, T>, bksge::tuple_element_t<0, T>>
>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_ITERATOR_SENTINEL_PAIR_HPP
