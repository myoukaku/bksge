/**
 *	@file	stable_sort.hpp
 *
 *	@brief	ranges::stable_sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_STABLE_SORT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_STABLE_SORT_HPP

#include <bksge/fnd/algorithm/stable_sort.hpp>
#include <bksge/fnd/algorithm/ranges/detail/make_comp_proj.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
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

struct stable_sort_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::random_access_iterator Iter,
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
			bksge::random_access_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::sortable<Iter, Comp, Proj>
		>::value>
	>
#endif
	Iter operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		auto lasti = ranges::next(first, last);
		bksge::stable_sort(
			std::move(first),
			lasti,
			detail::make_comp_proj(comp, proj));
		return lasti;
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::random_access_range Range,
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
			ranges::random_access_range<Range>,
			bksge::sortable<ranges::iterator_t<Range>, Comp, Proj>
		>::value>
	>
#endif
	ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR stable_sort_fn stable_sort{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_STABLE_SORT_HPP
