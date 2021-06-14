/**
 *	@file	partial_sort.hpp
 *
 *	@brief	partial_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_PARTIAL_SORT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_PARTIAL_SORT_HPP

#include <bksge/fnd/algorithm/detail/heap_select.hpp>
#include <bksge/fnd/algorithm/detail/sort_heap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	detail::heap_select(first, middle, last, comp);
	detail::sort_heap(first, middle, comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_PARTIAL_SORT_HPP
