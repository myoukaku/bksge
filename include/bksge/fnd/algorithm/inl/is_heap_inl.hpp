/**
 *	@file	is_heap_inl.hpp
 *
 *	@brief	is_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_IS_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_IS_HEAP_INL_HPP

#include <bksge/fnd/algorithm/is_heap.hpp>
#include <bksge/fnd/algorithm/is_heap_until.hpp>
#include <bksge/fnd/functional/less.hpp>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR bool
is_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	return bksge::algorithm::is_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR bool
is_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	return bksge::is_heap_until(first, last, comp) == last;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_IS_HEAP_INL_HPP
