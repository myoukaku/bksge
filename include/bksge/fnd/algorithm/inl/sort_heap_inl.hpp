/**
 *	@file	sort_heap_inl.hpp
 *
 *	@brief	sort_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SORT_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SORT_HEAP_INL_HPP

#include <bksge/fnd/algorithm/sort_heap.hpp>
#include <bksge/fnd/algorithm/detail/sort_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::sort_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
sort_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
    detail::sort_heap(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SORT_HEAP_INL_HPP
