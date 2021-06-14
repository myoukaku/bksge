/**
 *	@file	heap_select.hpp
 *
 *	@brief	heap_select の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_HEAP_SELECT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_HEAP_SELECT_HPP

#include <bksge/fnd/algorithm/detail/make_heap.hpp>
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
heap_select(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	detail::make_heap(first, middle, comp);
	for (auto i = middle; i < last; ++i)
	{
		if (comp(*i, *first))
		{
			detail::pop_heap(first, middle, i, comp);
		}
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_HEAP_SELECT_HPP
