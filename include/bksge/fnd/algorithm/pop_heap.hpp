/**
 *	@file	pop_heap.hpp
 *
 *	@brief	pop_heap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_POP_HEAP_HPP
#define BKSGE_FND_ALGORITHM_POP_HEAP_HPP

#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		ヒープ化された範囲の先頭と末尾を入れ替え、ヒープ範囲を作り直す
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	[first,last) は空でない heap でなければならない。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		first にある値を last - 1 と交換し、その後 [first,last - 1) が有効な heap となるように配置する。
 *
 *	@complexity	最大で 2 * log(last - first) 回比較する
 */
template <
	typename RandomAccessIterator,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
pop_heap(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		ヒープ化された範囲の先頭と末尾を入れ替え、ヒープ範囲を作り直す
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	[first,last) は空でない heap でなければならない。
 *				RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		first にある値を last - 1 と交換し、その後 [first,last - 1) が有効な heap となるように配置する。
 *
 *	@complexity	最大で 2 * log(last - first) 回比較する
 */
template <
	typename RandomAccessIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::pop_heap;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/pop_heap_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_POP_HEAP_HPP
