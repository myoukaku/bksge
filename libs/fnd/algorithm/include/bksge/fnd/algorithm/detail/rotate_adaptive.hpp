/**
 *	@file	rotate_adaptive.hpp
 *
 *	@brief	rotate_adaptive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_ROTATE_ADAPTIVE_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_ROTATE_ADAPTIVE_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/algorithm/rotate.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2,
	typename Distance
>
BidirectionalIterator1 rotate_adaptive(
	BidirectionalIterator1 first,
	BidirectionalIterator1 middle,
	BidirectionalIterator1 last,
	Distance len1,
	Distance len2,
	BidirectionalIterator2 buffer,
	Distance buffer_size)
{
	if (len1 > len2 && len2 <= buffer_size)
	{
		if (len2)
		{
			auto buffer_end = bksge::move(middle, last, buffer);
			bksge::move_backward(first, middle, last);
			return bksge::move(buffer, buffer_end, first);
		}
		else
		{
			return first;
		}
	}
	else if (len1 <= buffer_size)
	{
		if (len1)
		{
			auto buffer_end = bksge::move(first, middle, buffer);
			bksge::move(middle, last, first);
			return bksge::move_backward(buffer, buffer_end, last);
		}
		else
		{
			return last;
		}
	}
	else
	{
		return bksge::rotate(first, middle, last);
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_ROTATE_ADAPTIVE_HPP
