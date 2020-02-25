/**
 *	@file	is_heap.hpp
 *
 *	@brief	is_heap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_HEAP_HPP
#define BKSGE_FND_ALGORITHM_IS_HEAP_HPP

#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲がヒープ化されているか判定する
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		is_heap_until(first, last) == last
 *
 *	@complexity	線形時間
 */
template <
	typename RandomAccessIterator,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
is_heap(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		範囲がヒープ化されているか判定する
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		is_heap_until(first, last, comp) == last
 *
 *	@complexity	線形時間
 */
template <
	typename RandomAccessIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::is_heap;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_heap_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_HEAP_HPP
