/**
 *	@file	copy_if_inl.hpp
 *
 *	@brief	copy_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_COPY_IF_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_COPY_IF_INL_HPP

#include <bksge/fnd/algorithm/copy_if.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate,
	typename
>
inline OutputIterator
copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			*result++ = *first;
		}
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_COPY_IF_INL_HPP
