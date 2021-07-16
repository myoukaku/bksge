/**
 *	@file	mismatch.hpp
 *
 *	@brief	ranges::mismatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_MISMATCH_HPP
#define BKSGE_FND_ALGORITHM_RANGES_MISMATCH_HPP

#include <bksge/fnd/algorithm/ranges/in_in_result.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
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
using mismatch_result = in_in_result<Iter1, Iter2>;

struct mismatch_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_comparable<
		Iter1, Iter2, Pred, Proj1, Proj2>
#else
	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirectly_comparable<
				Iter1, Iter2, Pred, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR mismatch_result<Iter1, Iter2>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		while (first1 != last1 && first2 != last2 &&
			(bool)bksge::invoke(pred,
				bksge::invoke(proj1, *first1),
				bksge::invoke(proj2, *first2)))
		{
			++first1;
			++first2;
		}

		return { std::move(first1), std::move(first2) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range1,
		ranges::input_range Range2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_comparable<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>,
		Pred, Proj1, Proj2>
#else
	template <
		typename Range1,
		typename Range2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::input_range<Range2>,
			bksge::indirectly_comparable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>,
				Pred, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR mismatch_result<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>>
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

BKSGE_INLINE_VAR BKSGE_CONSTEXPR mismatch_fn mismatch{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_MISMATCH_HPP
