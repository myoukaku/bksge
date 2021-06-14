/**
 *	@file	partial_sort_inl.hpp
 *
 *	@brief	partial_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_INL_HPP

#include <bksge/fnd/algorithm/partial_sort.hpp>
#include <bksge/fnd/algorithm/detail/partial_sort.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator>
inline void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last)
{
	return bksge::algorithm::partial_sort(
		first, middle, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare>
inline void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp)
{
	detail::partial_sort(first, middle, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTIAL_SORT_INL_HPP
