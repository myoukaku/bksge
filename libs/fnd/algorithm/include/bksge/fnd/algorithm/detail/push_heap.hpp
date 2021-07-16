/**
 *	@file	push_heap.hpp
 *
 *	@brief	push_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_PUSH_HEAP_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_PUSH_HEAP_HPP

#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <
	typename RandomAccessIterator,
	typename Distance,
	typename T,
	typename Compare
>
inline BKSGE_CXX14_CONSTEXPR void
push_heap(
	RandomAccessIterator first,
	Distance hole_index,
	Distance top_index,
	T value,
	Compare& comp)
{
	Distance parent = (hole_index - 1) / 2;
	while (hole_index > top_index && comp(*(first + parent), value))
	{
		*(first + hole_index) = std::move(*(first + parent));
		hole_index = parent;
		parent = (hole_index - 1) / 2;
	}
	*(first + hole_index) = std::move(value);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_PUSH_HEAP_HPP
