/**
 *	@file	minmax_element.hpp
 *
 *	@brief	ranges::minmax_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_MINMAX_ELEMENT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_MINMAX_ELEMENT_HPP

#include <bksge/fnd/algorithm/ranges/min_max_result.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
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

template <typename Iter>
using minmax_element_result = min_max_result<Iter>;

struct minmax_element_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::forward_iterator Iter,
		bksge::sentinel_for<Iter> Sent,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<Iter, Proj>
		> Comp = ranges::less
#else
		typename Iter,
		typename Sent,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter>,
			bksge::sentinel_for<Sent, Iter>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<Iter, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR minmax_element_result<Iter>
	operator()(Iter first, Sent last,
		Comp comp = {}, Proj proj = {}) const
	{
		if (first == last)
		{
			return { first, first };
		}

		minmax_element_result<Iter> result = { first, first };
		auto i = first;
		while (++i != last)
		{
			if (bksge::invoke(comp,
				bksge::invoke(proj, *i),
				bksge::invoke(proj, *result.min)))
			{
				result.min = i;
			}

			if (!(bool)bksge::invoke(comp,
				bksge::invoke(proj, *i),
				bksge::invoke(proj, *result.max)))
			{
				result.max = i;
			}
		}

		return result;
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::forward_range Range,
		typename Proj = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<ranges::iterator_t<Range>, Proj>
		> Comp = ranges::less
#else
		typename Range,
		typename Proj = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<ranges::iterator_t<Range>, Proj>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR minmax_element_result<ranges::borrowed_iterator_t<Range>>
	operator()(Range&& r, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR minmax_element_fn minmax_element{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_MINMAX_ELEMENT_HPP
