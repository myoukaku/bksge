﻿/**
 *	@file	inplace_merge.hpp
 *
 *	@brief	ranges::inplace_merge の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_INPLACE_MERGE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_INPLACE_MERGE_HPP

#include <bksge/fnd/algorithm/inplace_merge.hpp>
#include <bksge/fnd/algorithm/ranges/detail/make_comp_proj.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
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

struct inplace_merge_fn
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
	Iter operator()(Iter first, Iter middle, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		auto lasti = ranges::next(first, last);
		bksge::inplace_merge(
			bksge::move(first),
			bksge::move(middle),
			lasti,
			detail::make_comp_proj(comp, proj));
		return lasti;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::bidirectional_range Range,
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
			ranges::bidirectional_range<Range>,
			bksge::sortable<ranges::iterator_t<Range>, Comp, Proj>
		>::value>
	>
#endif
	ranges::borrowed_iterator_t<Range>
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

BKSGE_INLINE_VAR BKSGE_CONSTEXPR inplace_merge_fn inplace_merge{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_INPLACE_MERGE_HPP
