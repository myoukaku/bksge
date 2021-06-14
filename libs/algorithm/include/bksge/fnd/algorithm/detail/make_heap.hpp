/**
 *	@file	make_heap.hpp
 *
 *	@brief	make_heap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_MAKE_HEAP_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_MAKE_HEAP_HPP

#include <bksge/fnd/algorithm/detail/adjust_heap.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare& comp)
{
	using value_t = bksge::iter_value_t<RandomAccessIterator>;
	using difference_t = bksge::iter_difference_t<RandomAccessIterator>;

	if (last - first < 2)
	{
		return;
	}

	const difference_t len = last - first;
	difference_t parent = (len - 2) / 2;
	for (;;)
	{
		value_t value = bksge::move(*(first + parent));
		detail::adjust_heap(first, parent, len, bksge::move(value), comp);

		if (parent == 0)
		{
			return;
		}

		parent--;
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_MAKE_HEAP_HPP
