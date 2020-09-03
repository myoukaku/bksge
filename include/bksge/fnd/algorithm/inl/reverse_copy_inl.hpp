/**
 *	@file	reverse_copy_inl.hpp
 *
 *	@brief	reverse_copy の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REVERSE_COPY_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REVERSE_COPY_INL_HPP

#include <bksge/fnd/algorithm/reverse_copy.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename BidirectionalIterator,
	typename OutputIterator
>
inline BKSGE_CXX14_CONSTEXPR OutputIterator
reverse_copy(
	BidirectionalIterator first,
	BidirectionalIterator last,
	OutputIterator result)
{
	while (first != last)
	{
		*result++ = *--last;
	}

	return result;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REVERSE_COPY_INL_HPP
