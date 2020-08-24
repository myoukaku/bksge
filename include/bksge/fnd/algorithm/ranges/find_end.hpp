/**
 *	@file	find_end.hpp
 *
 *	@brief	ranges::find_end の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_FIND_END_HPP
#define BKSGE_FND_ALGORITHM_RANGES_FIND_END_HPP

#include <bksge/fnd/algorithm/ranges/search.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/borrowed_subrange_t.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

struct find_end_fn
{
private:
	template <
		BKSGE_REQUIRES_PARAM(bksge::bidirectional_iterator, Iter1), typename Sent1,
		BKSGE_REQUIRES_PARAM(bksge::bidirectional_iterator, Iter2), typename Sent2,
		typename Pred,
		typename Proj1,
		typename Proj2
	>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter1>
	impl(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2,
		bksge::detail::overload_priority<1>)
	{
		auto i1 = ranges::next(first1, last1);
		auto i2 = ranges::next(first2, last2);
		auto rresult = ranges::search(
			bksge::reverse_iterator<Iter1>{i1},
			bksge::reverse_iterator<Iter1>{first1},
			bksge::reverse_iterator<Iter2>{i2},
			bksge::reverse_iterator<Iter2>{first2},
			bksge::move(pred),
			bksge::move(proj1),
			bksge::move(proj2));
		auto result_first = ranges::end(rresult).base();
		auto result_last  = ranges::begin(rresult).base();
		if (result_last == first1)
		{
			return { i1, i1 };
		}
		else
		{
			return { result_first, result_last };
		}
	}

	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred,
		typename Proj1,
		typename Proj2
	>
	static BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter1>
	impl(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred, Proj1 proj1, Proj2 proj2,
		bksge::detail::overload_priority<0>)
	{
		auto i = ranges::next(first1, last1);
		if (first2 == last2)
		{
			return { i, i };
		}

		auto result_begin = i;
		auto result_end   = i;

		for (;;)
		{
			auto new_range = ranges::search(
				first1, last1,
				first2, last2,
				pred, proj1, proj2);
			auto new_result_begin = ranges::begin(new_range);
			auto new_result_end   = ranges::end(new_range);
			if (new_result_begin == last1)
			{
				return { result_begin, result_end };
			}
			else
			{
				result_begin = new_result_begin;
				result_end   = new_result_end;
				first1 = result_begin;
				++first1;
			}
		}
	}

public:
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		bksge::forward_iterator Iter1, bksge::sentinel_for<Iter1> Sent1,
		bksge::forward_iterator Iter2, bksge::sentinel_for<Iter2> Sent2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
#else
	template <
		typename Iter1, typename Sent1,
		typename Iter2, typename Sent2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::forward_iterator<Iter1>, bksge::sentinel_for<Sent1, Iter1>,
			bksge::forward_iterator<Iter2>, bksge::sentinel_for<Sent2, Iter2>,
			bksge::indirectly_comparable<Iter1, Iter2, Pred, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::subrange<Iter1>
	operator()(
		Iter1 first1, Sent1 last1,
		Iter2 first2, Sent2 last2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return impl(
			bksge::move(first1), bksge::move(last1),
			bksge::move(first2), bksge::move(last2),
			bksge::move(pred),
			bksge::move(proj1),
			bksge::move(proj2),
			bksge::detail::overload_priority<1>{});
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <
		ranges::forward_range Range1,
		ranges::forward_range Range2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity
	>
	requires bksge::indirectly_comparable<
		ranges::iterator_t<Range1>,
		ranges::iterator_t<Range2>,
		Pred, Proj1, Proj2>
#else
	template <
		typename Range1,
		typename Range2,
		typename Pred = ranges::equal_to,
		typename Proj1 = bksge::identity,
		typename Proj2 = bksge::identity,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::forward_range<Range1>,
			ranges::forward_range<Range2>,
			bksge::indirectly_comparable<
				ranges::iterator_t<Range1>,
				ranges::iterator_t<Range2>,
				Pred, Proj1, Proj2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR ranges::borrowed_subrange_t<Range1>
	operator()(
		Range1&& r1,
		Range2&& r2,
		Pred pred = {},
		Proj1 proj1 = {},
		Proj2 proj2 = {}) const
	{
		return (*this)(
			ranges::begin(r1), ranges::end(r1),
			ranges::begin(r2), ranges::end(r2),
			bksge::move(pred),
			bksge::move(proj1),
			bksge::move(proj2));
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR find_end_fn find_end{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_FIND_END_HPP
