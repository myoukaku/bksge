/**
 *	@file	move_merge.hpp
 *
 *	@brief	move_merge の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_HPP

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename Compare
>
OutputIterator move_merge(
	InputIterator first1, InputIterator last1,
	InputIterator first2, InputIterator last2,
	OutputIterator result, Compare comp)
{
	while (first1 != last1 && first2 != last2)
	{
		if (comp(first2, first1))
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

	return
		bksge::move(first2, last2,
			bksge::move(first1, last1, result));
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MOVE_MERGE_HPP
