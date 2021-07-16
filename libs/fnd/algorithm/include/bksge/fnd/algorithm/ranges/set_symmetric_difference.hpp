/**
 *	@file	set_symmetric_difference.hpp
 *
 *	@brief	ranges::set_symmetric_difference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_SET_SYMMETRIC_DIFFERENCE_HPP
#define BKSGE_FND_ALGORITHM_RANGES_SET_SYMMETRIC_DIFFERENCE_HPP

#include <bksge/fnd/algorithm/ranges/in_in_out_result.hpp>
#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/mergeable.hpp>
#include <bksge/fnd/ranges/concepts/input_range.hpp>
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

template <typename Iter1, typename Iter2, typename Out>
using set_symmetric_difference_result =
	in_in_out_result<Iter1, Iter2, Out>;

struct set_symmetric_difference_fn
{
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::input_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::input_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		bksge::weakly_incrementable Out,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>
#else
	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Out,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::input_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::input_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::weakly_incrementable<Out>,
			bksge::mergeable<Iter1, Iter2, Out, Comp, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR set_symmetric_difference_result<Iter1, Iter2, Out>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Out result,
		Comp comp = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		while (first1 != last1 && first2 != last2)
		{
			if (bksge::invoke(comp,
				bksge::invoke(proj1, *first1),
				bksge::invoke(proj2, *first2)))
			{
				*result = *first1;
				++first1;
				++result;
			}
			else if (bksge::invoke(comp,
				bksge::invoke(proj2, *first2),
				bksge::invoke(proj1, *first1)))
			{
				*result = *first2;
				++first2;
				++result;
			}
			else
			{
				++first1;
				++first2;
			}
		}

		auto copy1 = ranges::copy(std::move(first1), std::move(last1), std::move(result));
		auto copy2 = ranges::copy(std::move(first2), std::move(last2), std::move(copy1.out));
		return { std::move(copy1.in), std::move(copy2.in), std::move(copy2.out) };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::input_range Range1,
		ranges::input_range Range2,
		bksge::weakly_incrementable Out,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::mergeable<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>,
		Out, Comp, Proj1, Proj2>
#else
	template <
		typename Range1,
		typename Range2,
		typename Out,
		typename Comp = ranges::less,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::input_range<Range1>,
			ranges::input_range<Range2>,
			bksge::weakly_incrementable<Out>,
			bksge::mergeable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>,
				Out, Comp, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR set_symmetric_difference_result<
		ranges::borrowed_iterator_t<Range1>,
		ranges::borrowed_iterator_t<Range2>,
		Out>
	operator()(
		Range1&& r1, Range2&& r2,
		Out result,
		Comp comp = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			std::move(result), std::move(comp),
			std::move(proj1), std::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR set_symmetric_difference_fn set_symmetric_difference{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_SET_SYMMETRIC_DIFFERENCE_HPP
