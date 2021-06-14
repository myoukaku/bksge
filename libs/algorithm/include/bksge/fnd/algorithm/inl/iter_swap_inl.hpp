/**
 *	@file	iter_swap_inl.hpp
 *
 *	@brief	iter_swap の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INL_ITER_SWAP_INL_HPP
#define BKSGE_FND_ALGORITHM_INL_ITER_SWAP_INL_HPP

#include <bksge/fnd/algorithm/iter_swap.hpp>
#include <bksge/fnd/utility/swap.hpp>

namespace bksge
{

namespace algorithm
{

template <typename ForwardIterator1, typename ForwardIterator2>
inline BKSGE_CXX14_CONSTEXPR void
iter_swap(ForwardIterator1 a, ForwardIterator2 b)
{
	bksge::swap(*a, *b);
}

}	// namespace algorithm

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_INL_ITER_SWAP_INL_HPP
