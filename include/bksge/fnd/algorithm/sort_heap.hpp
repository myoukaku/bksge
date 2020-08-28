/**
 *	@file	sort_heap.hpp
 *
 *	@brief	sort_heap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SORT_HEAP_HPP
#define BKSGE_FND_ALGORITHM_SORT_HEAP_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		ヒープ化された範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	[first,last) は有効なヒープである必要がある。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		ヒープ化されている [first,last) をソートする
 *
 *	@complexity	最大で N log(N) 回比較する（N == last - first）
 */
template <typename RandomAccessIterator>
BKSGE_CXX14_CONSTEXPR void
sort_heap(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		ヒープ化された範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,last) は有効なヒープである必要がある。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		ヒープ化されている [first,last) をソートする
 *
 *	@complexity	最大で N log(N) 回比較する（N == last - first）
 */
template <typename RandomAccessIterator, typename Compare>
BKSGE_CXX14_CONSTEXPR void
sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::sort_heap;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/sort_heap_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SORT_HEAP_HPP
