/**
 *	@file	partition_copy_inl.hpp
 *
 *	@brief	partition_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_PARTITION_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_PARTITION_COPY_INL_HPP

#include <bksge/fnd/algorithm/partition_copy.hpp>
#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/make_pair.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator1,
	typename OutputIterator2,
	typename Predicate,
	typename
>
inline BKSGE_CXX14_CONSTEXPR
bksge::pair<OutputIterator1, OutputIterator2>
partition_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator1 out_true,
	OutputIterator2 out_false,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			*out_true++ = *first;
		}
		else
		{
			*out_false++ = *first;
		}
	}

	return bksge::make_pair(out_true, out_false);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_PARTITION_COPY_INL_HPP
