/**
 *	@file	partial_sort.hpp
 *
 *	@brief	ranges::partial_sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_PARTIAL_SORT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_PARTIAL_SORT_HPP

#include <bksge/fnd/algorithm/ranges/make_heap.hpp>
#include <bksge/fnd/algorithm/ranges/pop_heap.hpp>
#include <bksge/fnd/algorithm/ranges/push_heap.hpp>
#include <bksge/fnd/algorithm/ranges/sort_heap.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/iter_swap.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct partial_sort_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::random_access_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Comp = ranges::less,
		typename Proj = bksge::identity
	>
	requires bksge::sortable<Iter, Comp, Proj>
#else
	template <
		typename Iter,
		typename Sent,
		typename Comp = ranges::less,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::random_access_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::sortable<Iter, Comp, Proj>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(Iter first, Iter middle, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == middle)
		{
			return ranges::next(first, last);
		}

		ranges::make_heap(first, middle, comp, proj);
		auto i = middle;
		for (; i != last; ++i)
		{
			if (bksge::invoke(comp,
				bksge::invoke(proj, *i),
				bksge::invoke(proj, *first)))
			{
				ranges::pop_heap(first, middle, comp, proj);
				ranges::iter_swap(middle-1, i);
				ranges::push_heap(first, middle, comp, proj);
			}
		}

		ranges::sort_heap(first, middle, comp, proj);

		return i;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::random_access_range Range,
		typename Comp = ranges::less,
		typename Proj = bksge::identity
	>
	requires bksge::sortable<ranges::iterator_t<Range>, Comp, Proj>
#else
	template <
		typename Range,
		typename Comp = ranges::less,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::random_access_range<Range>,
			bksge::sortable<ranges::iterator_t<Range>, Comp, Proj>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, ranges::iterator_t<Range> middle,
		Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r),
			bksge::move(middle),
			ranges::end(r),
			bksge::move(comp),
			bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR partial_sort_fn partial_sort{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_PARTIAL_SORT_HPP
