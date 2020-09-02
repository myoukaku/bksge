/**
 *	@file	sort_heap.hpp
 *
 *	@brief	sort_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_SORT_HEAP_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_SORT_HEAP_HPP

#include <bksge/fnd/algorithm/detail/pop_heap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare& comp)
{
	while (last - first > 1)
	{
		--last;
		detail::pop_heap(first, last, last, comp);
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_SORT_HEAP_HPP
