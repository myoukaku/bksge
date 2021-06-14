/**
 *	@file	merge_sort_loop.hpp
 *
 *	@brief	merge_sort_loop の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MERGE_SORT_LOOP_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MERGE_SORT_LOOP_HPP

#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/algorithm/detail/move_merge.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename RandomAccessIterator1,
	typename RandomAccessIterator2,
	typename Distance,
	typename Compare
>
void merge_sort_loop(
	RandomAccessIterator1 first,
	RandomAccessIterator1 last,
	RandomAccessIterator2 result,
	Distance step_size,
	Compare comp)
{
	const Distance two_step = 2 * step_size;

	while (last - first >= two_step)
	{
		result = detail::move_merge(
			first,
			first + step_size,
			first + step_size,
			first + two_step,
			result,
			comp);
		first += two_step;
	}

	step_size = bksge::min(Distance(last - first), step_size);

	detail::move_merge(
		first,
		first + step_size,
		first + step_size,
		last,
		result,
		comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MERGE_SORT_LOOP_HPP
