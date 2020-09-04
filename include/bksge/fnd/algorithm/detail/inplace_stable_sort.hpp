/**
 *	@file	inplace_stable_sort.hpp
 *
 *	@brief	inplace_stable_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_INPLACE_STABLE_SORT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_INPLACE_STABLE_SORT_HPP

#include <bksge/fnd/algorithm/detail/insertion_sort.hpp>
#include <bksge/fnd/algorithm/detail/merge_without_buffer.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
void inplace_stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	if (last - first < 15)
	{
		detail::insertion_sort(first, last, comp);
		return;
	}

	auto middle = first + (last - first) / 2;
	detail::inplace_stable_sort(first, middle, comp);
	detail::inplace_stable_sort(middle, last, comp);
	detail::merge_without_buffer(first, middle, last, middle - first, last - middle, comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_INPLACE_STABLE_SORT_HPP
