/**
 *	@file	count_if.hpp
 *
 *	@brief	ranges::count_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_COUNT_IF_HPP
#define BKSGE_FND_ALGORITHM_RANGES_COUNT_IF_HPP

#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
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

struct count_if_fn
{
	template<
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<Iter, Proj>
		> Pred
#else
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_unary_predicate<
				Pred, bksge::projected<Iter, Proj>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<Iter>
	operator()(Iter first, Sent last, Pred pred, Proj proj = {}) const
	{
		bksge::iter_difference_t<Iter> n = 0;
		for (; first != last; ++first)
		{
			if (bksge::invoke(pred, bksge::invoke(proj, *first)))
			{
				++n;
			}
		}

		return n;
	}

	template<
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::input_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Pred
#else
		typename Range,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::indirect_unary_predicate<
				Pred, bksge::projected<ranges::iterator_t<Range>, Proj>
			>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR ranges::range_difference_t<Range>
	operator()(Range&& r, Pred pred, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR count_if_fn count_if{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_COUNT_IF_HPP
