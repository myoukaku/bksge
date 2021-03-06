﻿/**
 *	@file	is_heap_until.hpp
 *
 *	@brief	ranges::is_heap_until の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IS_HEAP_UNTIL_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IS_HEAP_UNTIL_HPP

#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
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

struct is_heap_until_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::random_access_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<Iter, Proj>
		> Comp = ranges::less
#else
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::random_access_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<Iter, Proj>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last, Comp comp = {}, Proj proj = {}) const
	{
		using diff_t = bksge::iter_difference_t<Iter>;
		diff_t n = ranges::distance(first, last);
		diff_t parent = 0;
		diff_t child = 1;

		for (; child < n; ++child)
		{
			if (bksge::invoke(comp,
				bksge::invoke(proj, *(first + parent)),
				bksge::invoke(proj, *(first + child))))
			{
				return first + child;
			}
			else if ((child & 1) == 0)
			{
				++parent;
			}
		}

		return first + n;
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::random_access_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::less
#else
		typename Range,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::random_access_range<Range>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<ranges::iterator_t<Range>, Proj>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(comp), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR is_heap_until_fn is_heap_until{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IS_HEAP_UNTIL_HPP
