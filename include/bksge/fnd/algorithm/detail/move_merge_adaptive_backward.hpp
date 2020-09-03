/**
 *	@file	move_merge_adaptive_backward.hpp
 *
 *	@brief	move_merge_adaptive_backward の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_ADAPTIVE_BACKWARD_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_ADAPTIVE_BACKWARD_HPP

#include <bksge/fnd/algorithm/move_backward.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2,
	typename BidirectionalIterator3,
	typename Compare
>
void move_merge_adaptive_backward(
	BidirectionalIterator1 first1, BidirectionalIterator1 last1,
	BidirectionalIterator2 first2, BidirectionalIterator2 last2,
	BidirectionalIterator3 result,
	Compare comp)
{
	if (first1 == last1)
	{
		bksge::move_backward(first2, last2, result);
		return;
	}
	else if (first2 == last2)
	{
		return;
	}

	--last1;
	--last2;

	for (;;)
	{
		if (comp(*last2, *last1))
		{
			*--result = bksge::move(*last1);
			if (first1 == last1)
			{
				bksge::move_backward(first2, ++last2, result);
				return;
			}

			--last1;
		}
		else
		{
			*--result = bksge::move(*last2);
			if (first2 == last2)
			{
				return;
			}

			--last2;
		}
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_ADAPTIVE_BACKWARD_HPP
