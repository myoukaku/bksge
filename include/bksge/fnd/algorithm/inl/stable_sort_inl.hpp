/**
 *	@file	stable_sort_inl.hpp
 *
 *	@brief	stable_sort の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_STABLE_SORT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_STABLE_SORT_INL_HPP

#include <bksge/fnd/algorithm/stable_sort.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <algorithm>

namespace bksge
{

namespace algorithm
{

template <typename RandomAccessIterator, typename>
inline void
stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last)
{
	bksge::algorithm::stable_sort(first, last, bksge::less<>());
}

template <typename RandomAccessIterator, typename Compare, typename>
inline void
stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp)
{
	std::stable_sort(first, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_STABLE_SORT_INL_HPP
