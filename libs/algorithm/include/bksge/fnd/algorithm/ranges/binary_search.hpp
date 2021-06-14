/**
 *	@file	binary_search.hpp
 *
 *	@brief	ranges::binary_search の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_BINARY_SEARCH_HPP
#define BKSGE_FND_ALGORITHM_RANGES_BINARY_SEARCH_HPP

#include <bksge/fnd/algorithm/ranges/lower_bound.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
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

struct binary_search_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::forward_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename T,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			T const*, bksge::projected<Iter, Proj>
		> Comp = ranges::less
#else
		typename Iter,
		typename Sent,
		typename T,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_strict_weak_order<Comp,
				T const*, bksge::projected<Iter, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool
	operator()(Iter first, Sent last,
		T const& value, Comp comp = {}, Proj proj = {}) const
	{
		auto i = ranges::lower_bound(first, last, value, comp, proj);
		if (i == last)
		{
			return false;
		}

		return !(bool)bksge::invoke(
			comp, value, bksge::invoke(proj, *i));
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::forward_range Range,
		typename T,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			T const*,
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::less
#else
		typename Range,
		typename T,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirect_strict_weak_order<Comp,
				T const*,
				bksge::projected<ranges::iterator_t<Range>, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool
	operator()(Range&& r,
		T const& value, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, bksge::move(comp), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR binary_search_fn binary_search{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_BINARY_SEARCH_HPP
