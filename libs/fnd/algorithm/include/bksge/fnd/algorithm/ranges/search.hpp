/**
 *	@file	search.hpp
 *
 *	@brief	ranges::search の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_SEARCH_HPP
#define BKSGE_FND_ALGORITHM_RANGES_SEARCH_HPP

#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
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

struct search_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template<
		bksge::forward_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::forward_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
#else
	template<
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::forward_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter1>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		if (first1 == last1 || first2 == last2)
		{
			return { first1, first1 };
		}

		for (;;)
		{
			for (;;)
			{
				if (first1 == last1)
				{
					return { first1, first1 };
				}

				if (bksge::invoke(pred,
					bksge::invoke(proj1, *first1),
					bksge::invoke(proj2, *first2)))
				{
					break;
				}

				++first1;
			}

			auto cur1 = first1;
			auto cur2 = first2;

			for (;;)
			{
				if (++cur2 == last2)
				{
					return { first1, ++cur1 };
				}

				if (++cur1 == last1)
				{
					return { cur1, cur1 };
				}

				if (!(bool)bksge::invoke(pred,
					bksge::invoke(proj1, *cur1),
					bksge::invoke(proj2, *cur2)))
				{
					++first1;
					break;
				}
			}
		}
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template<
		ranges::forward_range Range1,
		ranges::forward_range Range2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_comparable<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>,
		Pred, Proj1, Proj2>
#else
	template<
		typename Range1,
		typename Range2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range1>,
			ranges::forward_range<Range2>,
			bksge::indirectly_comparable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>,
				Pred, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range1>
	operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			std::move(pred),
			std::move(proj1),
			std::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR search_fn search{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_SEARCH_HPP
