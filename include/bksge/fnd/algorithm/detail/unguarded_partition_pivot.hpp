/**
 *	@file	unguarded_partition_pivot.hpp
 *
 *	@brief	unguarded_partition_pivot の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_PARTITION_PIVOT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_PARTITION_PIVOT_HPP

#include <bksge/fnd/algorithm/detail/move_median_to_first.hpp>
#include <bksge/fnd/algorithm/detail/unguarded_partition.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Compare>
inline BKSGE_CXX14_CONSTEXPR RandomAccessIterator
unguarded_partition_pivot(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	auto mid = first + (last - first) / 2;
	detail::move_median_to_first(first, first + 1, mid, last - 1, comp);
	return detail::unguarded_partition(first + 1, last, first, comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_UNGUARDED_PARTITION_PIVOT_HPP
