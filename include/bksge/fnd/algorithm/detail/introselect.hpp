/**
 *	@file	introselect.hpp
 *
 *	@brief	introselect の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_DETAIL_INTROSELECT_HPP
#define BKSGE_FND_ALGORITHM_DETAIL_INTROSELECT_HPP

#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/algorithm/detail/heap_select.hpp>
#include <bksge/fnd/algorithm/detail/unguarded_partition_pivot.hpp>
#include <bksge/fnd/algorithm/detail/insertion_sort.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

namespace detail
{

template <typename RandomAccessIterator, typename Size, typename Compare>
inline BKSGE_CXX14_CONSTEXPR void
introselect(
	RandomAccessIterator first,
	RandomAccessIterator nth,
	RandomAccessIterator last,
	Size depth_limit,
	Compare comp)
{
	while (last - first > 3)
	{
		if (depth_limit == 0)
		{
			detail::heap_select(first, nth + 1, last, comp);
			// Place the nth largest element in its final position.
			bksge::iter_swap(first, nth);
			return;
		}

		--depth_limit;
		auto cut = detail::unguarded_partition_pivot(first, last, comp);

		if (cut <= nth)
		{
			first = cut;
		}
		else
		{
			last = cut;
		}
	}

	detail::insertion_sort(first, last, comp);
}

}	// namespace detail

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_DETAIL_INTROSELECT_HPP
