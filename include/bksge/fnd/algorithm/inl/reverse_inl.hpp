/**
 *	@file	reverse_inl.hpp
 *
 *	@brief	reverse の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_REVERSE_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_REVERSE_INL_HPP

#include <bksge/fnd/algorithm/reverse.hpp>
#include <bksge/fnd/algorithm/iter_swap.hpp>

namespace bksge
{

namespace algorithm
{

template <typename BidirectionalIterator, typename>
inline void
reverse(
	BidirectionalIterator first,
	BidirectionalIterator last)
{
	for (; first != last && first != --last; ++first)
	{
		bksge::iter_swap(first, last);
	}
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_REVERSE_INL_HPP
