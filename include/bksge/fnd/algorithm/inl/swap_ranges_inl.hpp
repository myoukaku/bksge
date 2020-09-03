/**
 *	@file	swap_ranges_inl.hpp
 *
 *	@brief	swap_ranges の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_SWAP_RANGES_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_SWAP_RANGES_INL_HPP

#include <bksge/fnd/algorithm/swap_ranges.hpp>
#include <bksge/fnd/algorithm/iter_swap.hpp>

namespace bksge
{

namespace algorithm
{

template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator2
swap_ranges(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2)
{
	while (first1 != last1)
	{
		bksge::iter_swap(first1++, first2++);
	}

	return first2;
}

template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
inline BKSGE_CXX14_CONSTEXPR ForwardIterator2
swap_ranges(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2)
{
	while (first1 != last1 && first2 != last2)
	{
		bksge::iter_swap(first1++, first2++);
	}

	return first2;
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_SWAP_RANGES_INL_HPP
