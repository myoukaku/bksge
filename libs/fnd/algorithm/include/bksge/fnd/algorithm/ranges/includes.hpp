/**
 *	@file	includes.hpp
 *
 *	@brief	ranges::includes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_INCLUDES_HPP
#define BKSGE_FND_ALGORITHM_RANGES_INCLUDES_HPP

#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirect_strict_weak_order.hpp>
#include <bksge/fnd/iterator/projected.hpp>
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

struct includes_fn
{
	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<Iter1, Proj1>,
			bksge::projected<Iter2, Proj2>
		> Comp = ranges::less
#else
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<Iter1, Proj1>,
				bksge::projected<Iter2, Proj2>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		while (first1 != last1 && first2 != last2)
		{
			if (bksge::invoke(comp,
				bksge::invoke(proj2, *first2),
				bksge::invoke(proj1, *first1)))
			{
				return false;
			}
			else if (bksge::invoke(comp,
				bksge::invoke(proj1, *first1),
				bksge::invoke(proj2, *first2)))
			{
				++first1;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		return first2 == last2;
	}

	template <
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		ranges::input_range Range1,
		ranges::input_range Range2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		bksge::indirect_strict_weak_order<
			bksge::projected<ranges::iterator_t<Range1>, Proj1>,
			bksge::projected<ranges::iterator_t<Range2>, Proj2>
		> Comp = ranges::less
#else
		typename Range1,
		typename Range2,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename Comp = ranges::less,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::input_range<Range2>,
			bksge::indirect_strict_weak_order<Comp,
				bksge::projected<ranges::iterator_t<Range1>, Proj1>,
				bksge::projected<ranges::iterator_t<Range2>, Proj2>>
		>::value>
#endif
	>
	BKSGE_CXX14_CONSTEXPR bool
	operator()(
		Range1&& r1, Range2&& r2,
		Comp  comp  = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			std::move(comp),
			std::move(proj1), std::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR includes_fn includes{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_INCLUDES_HPP
