/**
 *	@file	copy_backward.hpp
 *
 *	@brief	copy_backward の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COPY_BACKWARD_HPP
#define BKSGE_FND_ALGORITHM_COPY_BACKWARD_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された範囲の要素を後ろからコピーする
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
 *	@return		result + (last - first)
 *
 *	@effect		[first,last) 内にある要素を、それぞれ [result - (last-first),result) へコピーする。
 *				コピーは last - 1 から順番に行い、1 以上 last - first 以下であるそれぞれの n について、
 *				*(result - n) = *(last - n) を行う。
 *
 *	@complexity	正確に last - first 回代入が行われる。
 *
 *	@note		last が [result - (last-first), result) の範囲内にあるときには、
 *				copy() の代わりに copy_backward() を使うべきである。
 */
template <
	typename BidirectionalIterator1,
	typename BidirectionalIterator2
>
BKSGE_CXX14_CONSTEXPR BidirectionalIterator2
copy_backward(
	BidirectionalIterator1 first,
	BidirectionalIterator1 last,
	BidirectionalIterator2 result);

}	// namespace algorithm

using algorithm::copy_backward;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/copy_backward_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COPY_BACKWARD_HPP
