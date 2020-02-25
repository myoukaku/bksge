/**
 *	@file	inplace_merge_inl.hpp
 *
 *	@brief	inplace_merge の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_INPLACE_MERGE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_INPLACE_MERGE_INL_HPP

#include <bksge/fnd/algorithm/inplace_merge.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <algorithm>

namespace bksge
{

namespace algorithm
{

template <typename BidirectionalIterator, typename>
inline void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last)
{
	return bksge::algorithm::inplace_merge(
		first, middle, last, bksge::less<>());
}

template <typename BidirectionalIterator, typename Compare, typename>
inline void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Compare comp)
{
	return std::inplace_merge(
		first, middle, last, comp);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_INPLACE_MERGE_INL_HPP
