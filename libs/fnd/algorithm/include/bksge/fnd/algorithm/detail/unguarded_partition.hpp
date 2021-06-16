/**
 *	@file	unguarded_partition.hpp
 *
 *	@brief	unguarded_partition の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_PARTITION_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_PARTITION_HPP

#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
unguarded_partition(
	RandomAccessIterator first,
	RandomAccessIterator last,
	RandomAccessIterator pivot,
	Compare comp)
{
	while (true)
	{
		while (comp(*first, *pivot))
		{
			++first;
		}

		--last;
		while (comp(*pivot, *last))
		{
			--last;
		}

		if (!(first < last))
		{
			return first;
		}

		bksge::iter_swap(first, last);
		++first;
	}
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_PARTITION_HPP
