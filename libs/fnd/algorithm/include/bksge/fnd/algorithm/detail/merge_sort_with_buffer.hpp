/**
 *	@file	merge_sort_with_buffer.hpp
 *
 *	@brief	merge_sort_with_buffer の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MERGE_SORT_WITH_BUFFER_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MERGE_SORT_WITH_BUFFER_HPP

#include <bksge/fnd/algorithm/detail/chunk_insertion_sort.hpp>
#include <bksge/fnd/algorithm/detail/merge_sort_loop.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

enum { s_merge_sort_chunk_size = 7 };

template <
	typename RandomAccessIterator,
	typename Pointer,
	typename Compare
>
void merge_sort_with_buffer(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Pointer buffer,
	Compare comp)
{
	using difference_t = bksge::iter_difference_t<RandomAccessIterator>;

	const difference_t len = last - first;
	const Pointer buffer_last = buffer + len;

	difference_t step_size = s_merge_sort_chunk_size;
	detail::chunk_insertion_sort(first, last, step_size, comp);

	while (step_size < len)
	{
		detail::merge_sort_loop(first, last, buffer, step_size, comp);
		step_size *= 2;
		detail::merge_sort_loop(buffer, buffer_last, first, step_size, comp);
		step_size *= 2;
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MERGE_SORT_WITH_BUFFER_HPP
