/**
 *	@file	make_heap_inl.hpp
 *
 *	@brief	make_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_MAKE_HEAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_MAKE_HEAP_INL_HPP

#include <bksge/fnd/algorithm/make_heap.hpp>
#include <bksge/fnd/algorithm/detail/make_heap.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator>
inline BKSGE_CXX14_CONSTEXPR void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::make_heap(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
make_heap(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	detail::make_heap(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_MAKE_HEAP_INL_HPP
