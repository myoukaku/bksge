/**
 *	@file	iter_swap.hpp
 *
 *	@brief	iter_swap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_ITER_SWAP_HPP
#define BKSGE_FND_ALGORITHM_ITER_SWAP_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		2つのイテレータの要素を入れ替える
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		a
 *	@param		b
 *
 *	@require	a と b は Dereferenceable でなければならない。
 *				*a は *b と Swappable でなければならない。
 *
 *	@effect		swap(*a, *b)
 */
template <typename ForwardIterator1, typename ForwardIterator2>
BKSGE_CXX14_CONSTEXPR void
iter_swap(ForwardIterator1 a, ForwardIterator2 b);

}	// namespace algorithm

using algorithm::iter_swap;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/iter_swap_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_ITER_SWAP_HPP
