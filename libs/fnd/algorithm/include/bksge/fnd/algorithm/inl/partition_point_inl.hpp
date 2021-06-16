/**
 *	@file	partition_point_inl.hpp
 *
 *	@brief	partition_point の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PARTITION_POINT_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PARTITION_POINT_INL_HPP

#include <bksge/fnd/algorithm/partition_point.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/next.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator, typename Predicate>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator
partition_point(
	ForwardIterator first,
	ForwardIterator last,
	Predicate pred)
{
	for (auto len = bksge::distance(first, last); len != 0;)
	{
		auto half = len / 2;
		auto mid = bksge::next(first, half);

		if (pred(*mid))
		{
			len -= half + 1;
			first = bksge::next(mid);
		}
		else
		{
			len = half;
		}
	}

	return first;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTITION_POINT_INL_HPP
