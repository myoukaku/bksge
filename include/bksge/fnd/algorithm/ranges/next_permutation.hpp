/**
 *	@file	next_permutation.hpp
 *
 *	@brief	ranges::next_permutation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_NEXT_PERMUTATION_HPP
#define BKSGE_FND_ALGORITHM_RANGES_NEXT_PERMUTATION_HPP

#include <bksge/fnd/algorithm/ranges/in_found_result.hpp>
#include <bksge/fnd/algorithm/ranges/reverse.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/iter_swap.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
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

template <typename Iter>
using next_permutation_result = in_found_result<Iter>;

struct next_permutation_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::bidirectional_iterator Iter,
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
			bksge::bidirectional_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::sortable<Iter, Comp, Proj>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR next_permutation_result<Iter>
	operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return { bksge::move(first), false };
		}

		auto i = first;
		++i;
		if (i == last)
		{
			return { bksge::move(i), false };
		}

		auto lasti = ranges::next(first, last);
		i = lasti;
		--i;

		for (;;)
		{
			auto ii = i;
			--i;
			if (bksge::invoke(comp,
				bksge::invoke(proj, *i),
				bksge::invoke(proj, *ii)))
			{
				auto j = lasti;
				while (!(bool)bksge::invoke(comp,
					bksge::invoke(proj, *i),
					bksge::invoke(proj, *--j)))
				{
					;
				}

				ranges::iter_swap(i, j);
				ranges::reverse(ii, last);
				return { bksge::move(lasti), true };
			}

			if (i == first)
			{
				ranges::reverse(first, last);
				return { bksge::move(lasti), false };
			}
		}
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::bidirectional_range Range,
		typename Comp = ranges::less,
		typename Proj = bksge::identity
	>
	requires bksge::sortable<
		ranges::iterator_t<Range>, Comp, Proj>
#else
	template <
		typename Range,
		typename Comp = ranges::less,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::bidirectional_range<Range>,
			bksge::sortable<
				ranges::iterator_t<Range>, Comp, Proj>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	next_permutation_result<ranges::borrowed_iterator_t<Range>>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			bksge::move(comp), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR next_permutation_fn next_permutation{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_NEXT_PERMUTATION_HPP
