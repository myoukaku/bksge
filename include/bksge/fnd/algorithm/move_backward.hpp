/**
 *	@file	move_backward.hpp
 *
 *	@brief	move_backward の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MOVE_BACKWARD_HPP
#define BKSGE_FND_ALGORITHM_MOVE_BACKWARD_HPP

#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された範囲の要素を後ろからムーブする
 *
 *	@tparam		BidirectionalIterator1
 *	@tparam		BidirectionalIterator2
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	result は (first,last] の範囲に含まれてはならない
 *
 *	@return		result - (last - first)
 *
 *	@effect		[first,last) 内にある要素を、それぞれ [result - (last-first),result) へムーブする。
 *				ムーブは last - 1 から順番に行い、1 以上 last - first 以下であるそれぞれの n について、
 *				*(result - n) = std::move(*(last - n)) を行う。
 *
 *	@complexity	正確に last - first 回ムーブ代入が行われる。
 *
 *	@note		last が [result - (last-first),result) の範囲内にあるときには、
 *				move() の代わりに move_backward() を使うべきである。
 */
template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator1>::value &&
		bksge::is_bidirectional_iterator<BidirectionalIterator2>::value
	>
>
BidirectionalIterator2
move_backward(
	BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result);

}	// namespace algorithm

using algorithm::move_backward;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/move_backward_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MOVE_BACKWARD_HPP
