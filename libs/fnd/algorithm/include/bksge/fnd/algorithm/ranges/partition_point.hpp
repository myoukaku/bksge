/**
 *	@file	partition_point.hpp
 *
 *	@brief	ranges::partition_point の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_PARTITION_POINT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_PARTITION_POINT_HPP

#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/iterator/ranges/advance.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
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

struct partition_point_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::forward_iterator Iter,
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
			bksge::forward_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<Iter, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(
		Iter first, Sent last,
		Pred pred, Proj proj = {}) const
	{
		auto len = ranges::distance(first, last);

		while (len > 0)
		{
			auto half = len / 2;
			auto middle = first;
			ranges::advance(middle, half);
			if (bksge::invoke(pred, bksge::invoke(proj, *middle)))
			{
				first = middle;
				++first;
				len = len - half - 1;
			}
			else
			{
				len = half;
			}
		}

		return first;
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::forward_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_unary_predicate<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Pred
#else
		typename Range,
		typename Proj = bksge::identity,
		typename Pred,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirect_unary_predicate<Pred,
				bksge::projected<ranges::iterator_t<Range>, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Pred pred, Proj proj = {}) const
{
	return (*this)(
		ranges::begin(r), ranges::end(r),
		std::move(pred), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR partition_point_fn partition_point{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_PARTITION_POINT_HPP
