/**
 *	@file	adjacent_find.hpp
 *
 *	@brief	ranges::adjacent_find の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_ADJACENT_FIND_HPP
#define BKSGE_FND_ALGORITHM_RANGES_ADJACENT_FIND_HPP

#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_binary_predicate.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
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

struct adjacent_find_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::forward_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_binary_predicate<
			bksge::projected<Iter, Proj>,
			bksge::projected<Iter, Proj>
		> Pred = ranges::equal_to
#else
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Pred = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_binary_predicate<
				Pred,
				bksge::projected<Iter, Proj>,
				bksge::projected<Iter, Proj>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last, Pred pred = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return first;
		}

		auto next = first;
		for (; ++next != last; first = next)
		{
			if (bksge::invoke(pred,
				bksge::invoke(proj, *first),
				bksge::invoke(proj, *next)))
			{
				return first;
			}
		}

		return next;
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::forward_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_binary_predicate<
			bksge::projected<iterator_t<Range>, Proj>,
			bksge::projected<iterator_t<Range>, Proj>
		> Pred = ranges::equal_to
#else
		typename Range,
		typename Proj = bksge::identity,
		typename Pred = ranges::equal_to,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirect_binary_predicate<
				Pred,
				bksge::projected<iterator_t<Range>, Proj>,
				bksge::projected<iterator_t<Range>, Proj>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Pred pred = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(pred), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR adjacent_find_fn adjacent_find{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_ADJACENT_FIND_HPP
