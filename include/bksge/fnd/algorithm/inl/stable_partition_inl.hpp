/**
 *	@file	stable_partition_inl.hpp
 *
 *	@brief	stable_partition の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_STABLE_PARTITION_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_STABLE_PARTITION_INL_HPP

#include <bksge/fnd/algorithm/stable_partition.hpp>
#include <algorithm>

namespace bksge
{

namespace algorithm
{

template <typename BidirectionalIterator, typename Predicate>
inline BidirectionalIterator
stable_partition(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Predicate pred)
{
	return std::stable_partition(first, last, pred);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_STABLE_PARTITION_INL_HPP
