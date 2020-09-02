/**
 *	@file	pop_heap_inl.hpp
 *
 *	@brief	pop_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_POP_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_POP_HEAP_INL_HPP

#include <bksge/fnd/algorithm/pop_heap.hpp>
#include <bksge/fnd/algorithm/detail/pop_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::pop_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
pop_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	if (last - first > 1)
	{
		--last;
		detail::pop_heap(first, last, last, comp);
	}
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_POP_HEAP_INL_HPP
