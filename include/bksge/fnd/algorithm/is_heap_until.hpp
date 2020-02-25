/**
 *	@file	is_heap_until.hpp
 *
 *	@brief	is_heap_until の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_HEAP_UNTIL_HPP
#define BKSGE_FND_ALGORITHM_IS_HEAP_UNTIL_HPP

#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲がヒープ化されているか判定し、ヒープ化されていない最初の要素を指すイテレータを取得する
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		distance(first, last) < 2 の場合は last を返す。
 *				そうでない場合、[first,last] 内のイテレータ i について、
 *				[first,i) が heap であるような最後の i を返す。
 *
 *	@complexity	線形時間
 */
template <
	typename RandomAccessIterator,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		範囲がヒープ化されているか判定し、ヒープ化されていない最初の要素を指すイテレータを取得する
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		distance(first, last) < 2 の場合は last を返す。
 *				そうでない場合、[first,last] 内のイテレータ i について、
 *				[first,i) が heap であるような最後の i を返す。
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
BKSGE_CXX14_CONSTEXPR RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::is_heap_until;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_heap_until_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_HEAP_UNTIL_HPP
