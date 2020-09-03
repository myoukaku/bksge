/**
 *	@file	move_merge_adaptive.hpp
 *
 *	@brief	move_merge_adaptive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_ADAPTIVE_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_ADAPTIVE_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare
>
void move_merge_adaptive(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result, Compare comp)
{
	while (first1 != last1 && first2 != last2)
	{
		if (comp(*first2, *first1))
		{
			*result = bksge::move(*first2);
			++first2;
		}
		else
		{
			*result = bksge::move(*first1);
			++first1;
		}

		++result;
	}

	if (first1 != last1)
	{
		bksge::move(first1, last1, result);
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_ADAPTIVE_HPP
