/**
 *	@file	push_heap.hpp
 *
 *	@brief	push_heap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PUSH_HEAP_HPP
#define BKSGE_FND_ALGORITHM_PUSH_HEAP_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		ヒープ化された範囲に要素を追加したヒープ範囲を得る
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	[first,last - 1) は有効な heap である必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		last - 1 の値を、[first,last) が有効な heap となるように配置する
 *
 *	@complexity	最大で log(last - first) 回比較する。
 */
template <typename RandomAccessIterator>
BKSGE_CXX14_CONSTEXPR void
push_heap(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		ヒープ化された範囲に要素を追加したヒープ範囲を得る
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,last - 1) は有効な heap である必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		last - 1 の値を、[first,last) が有効な heap となるように配置する
 *
 *	@complexity	最大で log(last - first) 回比較する。
 */
template <typename RandomAccessIterator, typename Compare>
BKSGE_CXX14_CONSTEXPR void
push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::push_heap;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/push_heap_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PUSH_HEAP_HPP
