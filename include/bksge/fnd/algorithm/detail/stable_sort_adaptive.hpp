/**
 *	@file	stable_sort_adaptive.hpp
 *
 *	@brief	stable_sort_adaptive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_STABLE_SORT_ADAPTIVE_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_STABLE_SORT_ADAPTIVE_HPP

#include <bksge/fnd/algorithm/detail/merge_sort_with_buffer.hpp>
#include <bksge/fnd/algorithm/detail/merge_adaptive.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename RandomAccessIterator,
	typename Pointer,
	typename Distance,
	typename Compare
>
void stable_sort_adaptive(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Pointer buffer,
	Distance buffer_size,
	Compare comp)
{
	const Distance len = (last - first + 1) / 2;
	const auto middle = first + len;

	if (len > buffer_size)
	{
		detail::stable_sort_adaptive(first, middle, buffer, buffer_size, comp);
		detail::stable_sort_adaptive(middle, last, buffer, buffer_size, comp);
	}
	else
	{
		detail::merge_sort_with_buffer(first, middle, buffer, comp);
		detail::merge_sort_with_buffer(middle, last, buffer, comp);
	}

	detail::merge_adaptive(
		first,
		middle,
		last,
		Distance(middle - first),
		Distance(last - middle),
		buffer, buffer_size,
		comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_STABLE_SORT_ADAPTIVE_HPP
