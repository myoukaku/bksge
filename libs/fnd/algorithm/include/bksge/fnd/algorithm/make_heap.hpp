﻿/**
 *	@file	make_heap.hpp
 *
 *	@brief	make_heap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MAKE_HEAP_HPP
#define BKSGE_FND_ALGORITHM_MAKE_HEAP_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲をヒープ化する
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	*first の型は MoveConstructible と MoveAssignable の要件を満たしていること
 *
 *	@effect		[first,last) の範囲で heap を構築する
 *
 *	@complexity	最大で 3 * (last - first) 回比較する
 */
template <typename RandomAccessIterator>
BKSGE_CXX14_CONSTEXPR void
make_heap(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		範囲をヒープ化する
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	*first の型は MoveConstructible と MoveAssignable の要件を満たしていること
 *
 *	@effect		[first,last) の範囲で heap を構築する
 *
 *	@complexity	最大で 3 * (last - first) 回比較する
 */
template <typename RandomAccessIterator, typename Compare>
BKSGE_CXX14_CONSTEXPR void
make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::make_heap;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/make_heap_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MAKE_HEAP_HPP
