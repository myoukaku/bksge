/**
 *	@file	adjust_heap.hpp
 *
 *	@brief	adjust_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_ADJUST_HEAP_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_ADJUST_HEAP_HPP

#include <bksge/fnd/algorithm/detail/push_heap.hpp>
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
adjust_heap(
	RandomAccessIterator first,
	Distance hole_index,
	Distance len,
	T value,
	Compare comp)
{
	const Distance top_index = hole_index;
	Distance second_child = hole_index;
	while (second_child < (len - 1) / 2)
	{
		second_child = 2 * (second_child + 1);
		if (comp(*(first + second_child), *(first + (second_child - 1))))
		{
			second_child--;
		}

		*(first + hole_index) = std::move(*(first + second_child));
		hole_index = second_child;
	}

	if ((len & 1) == 0 && second_child == (len - 2) / 2)
	{
		second_child = 2 * (second_child + 1);
		*(first + hole_index) = std::move(*(first + (second_child - 1)));
		hole_index = second_child - 1;
	}

	detail::push_heap(first, hole_index, top_index, std::move(value), comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_ADJUST_HEAP_HPP
