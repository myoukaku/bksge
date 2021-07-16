/**
 *	@file	stable_partition_adaptive.hpp
 *
 *	@brief	stable_partition_adaptive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_STABLE_PARTITION_ADAPTIVE_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_STABLE_PARTITION_ADAPTIVE_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/algorithm/rotate.hpp>
#include <bksge/fnd/algorithm/detail/find_if_not_n.hpp>
#include <bksge/fnd/iterator/advance.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename ForwardIterator,
	typename Pointer,
	typename Predicate,
	typename Distance
>
ForwardIterator stable_partition_adaptive(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred,
	Distance len,
	Pointer buffer,
	Distance buffer_size)
{
	if (len == 1)
	{
		return first;
	}

	if (len <= buffer_size)
	{
		ForwardIterator result1 = first;
		Pointer result2 = buffer;

		// The precondition guarantees that !pred(first), so
		// move that element to the buffer before starting the loop.
		// This ensures that we only call pred once per element.
		*result2 = std::move(*first);
		++result2;
		++first;
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				*result1 = std::move(*first);
				++result1;
			}
			else
			{
				*result2 = std::move(*first);
				++result2;
			}
		}

		bksge::move(buffer, result2, result1);
		return result1;
	}

	ForwardIterator middle = first;
	bksge::advance(middle, len / 2);
	ForwardIterator left_split = detail::stable_partition_adaptive(
		first, middle, pred, len / 2, buffer, buffer_size);

	// Advance past true-predicate values to satisfy this
	// function's preconditions.
	Distance right_len = len - len / 2;
	ForwardIterator right_split =
		detail::find_if_not_n(middle, right_len, pred);

	if (right_len)
	{
		right_split = detail::stable_partition_adaptive(
			right_split, last, pred, right_len, buffer, buffer_size);
	}

	return bksge::rotate(left_split, middle, right_split);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_STABLE_PARTITION_ADAPTIVE_HPP
