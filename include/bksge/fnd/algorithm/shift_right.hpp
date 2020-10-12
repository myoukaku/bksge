/**
 *	@file	shift_right.hpp
 *
 *	@brief	shift_right の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SHIFT_RIGHT_HPP
#define BKSGE_FND_ALGORITHM_SHIFT_RIGHT_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename BidirectionalIterator, typename Difference,
	typename Cat = typename bksge::iterator_traits<BidirectionalIterator>::iterator_category,
	typename = bksge::enable_if_t<bksge::is_derived_from<Cat, bksge::bidirectional_iterator_tag>::value>
>
BKSGE_CXX14_CONSTEXPR BidirectionalIterator
shift_right_impl(BidirectionalIterator first, BidirectionalIterator last, Difference n, bksge::detail::overload_priority<1>)
{
	auto mid = ranges::next(last, -n, first);
	if (mid == first)
	{
		return last;
	}

	return bksge::move_backward(bksge::move(first), bksge::move(mid), bksge::move(last));
}

template <typename ForwardIterator, typename Difference>
BKSGE_CXX14_CONSTEXPR ForwardIterator
shift_right_impl(ForwardIterator first, ForwardIterator last, Difference n, bksge::detail::overload_priority<0>)
{
	auto result = ranges::next(first, n, last);
	if (result == last)
	{
		return last;
	}

	auto dest_head = first;
	auto dest_tail = result;
	while (dest_head != result)
	{
		if (dest_tail == last)
		{
			// If we get here, then we must have
			//     2*n >= distance(first, last)
			// i.e. we are shifting out at least half of the range.  In
			// this case we can safely perform the shift with a single
			// move.
			bksge::move(bksge::move(first), bksge::move(dest_head), bksge::move(result));
			return result;
		}
		++dest_head;
		++dest_tail;
	}

	for (;;)
	{
		// At the start of each iteration of this outer loop, the range
		// [first, result) contains those elements that after shifting
		// the whole range right by n, should end up in
		// [dest_head, dest_tail) in order.

		// The below inner loop swaps the elements of [first, result)
		// and [dest_head, dest_tail), while simultaneously shifting
		// the latter range by n.
		auto cursor = first;
		while (cursor != result)
		{
			if (dest_tail == last)
			{
				// At this point the ranges [first, result) and
				// [dest_head, dest_tail) are disjoint, so we can safely
				// move the remaining elements.
				dest_head = bksge::move(cursor, result, bksge::move(dest_head));
				bksge::move(bksge::move(first), bksge::move(cursor), bksge::move(dest_head));
				return result;
			}
			bksge::iter_swap(cursor, dest_head);
			++dest_head;
			++dest_tail;
			++cursor;
		}
	}
}

}	// namespace detail

template <typename ForwardIterator>
BKSGE_CXX14_CONSTEXPR ForwardIterator
shift_right(ForwardIterator first, ForwardIterator last,
	typename bksge::iterator_traits<ForwardIterator>::difference_type n)
{
	if (n <= 0)
	{
		return first;
	}

	return detail::shift_right_impl(
		bksge::move(first),
		bksge::move(last),
		n,
		bksge::detail::overload_priority<1>{});
}

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_SHIFT_RIGHT_HPP
