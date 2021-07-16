/**
 *	@file	swap_ranges.hpp
 *
 *	@brief	ranges::swap_ranges の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_SWAP_RANGES_HPP
#define BKSGE_FND_ALGORITHM_RANGES_SWAP_RANGES_HPP

#include <bksge/fnd/algorithm/ranges/in_in_result.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter1, typename Iter2>
using swap_ranges_result = in_in_result<Iter1, Iter2>;

struct swap_ranges_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2
	>
	requires bksge::indirectly_swappable<Iter1, Iter2>
#else
	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirectly_swappable<Iter1, Iter2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR swap_ranges_result<Iter1, Iter2>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2) const
	{
		for (; first1 != last1 && first2 != last2; ++first1, (void)++first2)
		{
			ranges::iter_swap(first1, first2);
		}

		return { std::move(first1), std::move(first2) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::input_range Range1, ranges::input_range Range2>
	requires bksge::indirectly_swappable<
		ranges::iterator_t<Range1>, ranges::iterator_t<Range2>
	>
#else
	template <typename Range1, typename Range2,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>, ranges::input_range<Range2>,
			bksge::indirectly_swappable<
				ranges::iterator_t<Range1>, ranges::iterator_t<Range2>
			>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR swap_ranges_result<
		ranges::borrowed_iterator_t<Range1>,
		ranges::borrowed_iterator_t<Range2>>
	operator()(Range1&& r1, Range2&& r2) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR swap_ranges_fn swap_ranges{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_SWAP_RANGES_HPP
