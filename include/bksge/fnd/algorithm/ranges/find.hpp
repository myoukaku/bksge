﻿/**
 *	@file	find.hpp
 *
 *	@brief	ranges::find の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_FIND_HPP
#define BKSGE_FND_ALGORITHM_RANGES_FIND_HPP

#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_binary_predicate.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
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

struct find_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T,
		typename Proj = bksge::identity
	>
	requires bksge::indirect_binary_predicate<
		ranges::equal_to,
		bksge::projected<Iter, Proj>,
		T const*>
#else
	template <
		typename Iter,
		typename Sent,
		typename T,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<Iter, Proj>,
				T const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Iter operator()(
		Iter first, Sent last, T const& value, Proj proj = {}) const
	{
		while (first != last && !(bksge::invoke(proj, *first) == value))
		{
			++first;
		}

		return first;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range,
		typename T,
		typename Proj = bksge::identity
	>
	requires bksge::indirect_binary_predicate<
		ranges::equal_to,
		bksge::projected<ranges::iterator_t<Range>, Proj>,
		T const*>
#else
	template <
		typename Range,
		typename T,
		typename Proj = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range>,
			bksge::indirect_binary_predicate<
				ranges::equal_to,
				bksge::projected<ranges::iterator_t<Range>, Proj>,
				T const*>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, T const& value, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r), value, bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR find_fn find{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_FIND_HPP