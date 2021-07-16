/**
 *	@file	lower_bound.hpp
 *
 *	@brief	ranges::lower_bound の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_LOWER_BOUND_HPP
#define BKSGE_FND_ALGORITHM_RANGES_LOWER_BOUND_HPP

#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
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

struct lower_bound_fn
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
	BKSGE_CXX14_CONSTEXPR Iter
	operator()(
		Iter first, Sent last,
		T const& value, Comp comp = {}, Proj proj = {}) const
	{
		auto len = ranges::distance(first, last);

		while (len > 0)
		{
			auto half = len / 2;
			auto middle = first;
			ranges::advance(middle, half);
			if (bksge::invoke(comp, bksge::invoke(proj, *middle), value))
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
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, T const& value, Comp comp = {}, Proj proj = {}) const
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			value, std::move(comp), std::move(proj));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR lower_bound_fn lower_bound{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_LOWER_BOUND_HPP
