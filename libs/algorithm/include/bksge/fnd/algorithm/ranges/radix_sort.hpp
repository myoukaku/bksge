/**
 *	@file	radix_sort.hpp
 *
 *	@brief	ranges::radix_sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_RADIX_SORT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_RADIX_SORT_HPP

#include <bksge/fnd/algorithm/radix_sort.hpp>
#include <bksge/fnd/algorithm/ranges/detail/radix_sortable.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/borrowed_iterator_t.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct radix_sort_fn
{
	template <
		BKSGE_REQUIRES_PARAM(bksge::random_access_iterator, Iter),
		BKSGE_REQUIRES_PARAM_2(bksge::sentinel_for, Iter, Sent),
		typename Proj = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::ranges::detail::radix_sortable<Iter, Proj>
#else
		, typename = bksge::enable_if_t<
			bksge::ranges::detail::radix_sortable<Iter, Proj>::value
		>
	>
#endif
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(Iter first, Sent last, Proj proj = {}) const
	{
		auto lasti = ranges::next(first, last);
		bksge::radix_sort(bksge::move(first), lasti, proj);
		return lasti;
	}

	template <
		BKSGE_REQUIRES_PARAM(ranges::random_access_range, Range),
		typename Proj = bksge::identity
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	>
	requires bksge::ranges::detail::radix_sortable<ranges::iterator_t<Range>, Proj>
#else
		, typename = bksge::enable_if_t<
			bksge::ranges::detail::radix_sortable<ranges::iterator_t<Range>, Proj>::value
		>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, Proj proj = {}) const
	{
		return (*this)(ranges::begin(r), ranges::end(r), bksge::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR radix_sort_fn radix_sort{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_RADIX_SORT_HPP
