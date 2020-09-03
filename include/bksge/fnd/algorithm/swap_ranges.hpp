/**
 *	@file	swap_ranges.hpp
 *
 *	@brief	swap_ranges の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SWAP_RANGES_HPP
#define BKSGE_FND_ALGORITHM_SWAP_RANGES_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された2つの範囲同士を swap する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *
 *	以下、last1 - first1 を N とする。
 *
 *	@return		first2 + N
 *
 *	@require	[first1,last1) と [first2,first2 + N) の範囲が重なってはならない。
 *				0 以上 N 未満のそれぞれの n について、
 *				*(first1 + n) と *(first2 + n) は Swappable でなければならない。
 *
 *	@effect		0 以上 N 以下のそれぞれの n について
 *				swap(*(first1 + n), *(first2 + n)) を行う
 *
 *	@complexity	正確に N 回のスワップが行われる
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
BKSGE_CXX14_CONSTEXPR ForwardIterator2
swap_ranges(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2);

/**
 *	@brief		指定された2つの範囲同士を swap する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	以下、min(last1 - first1, last2 - first2) を N とする。
 *
 *	@return		first2 + N
 *
 *	@require	[first1,last1) と [first2,last2) の範囲が重なってはならない。
 *				0 以上 N 未満のそれぞれの n について、
 *				*(first1 + n) と *(first2 + n) は Swappable でなければならない。
 *
 *	@effect		0 以上 N 以下のそれぞれの n について
 *				swap(*(first1 + n), *(first2 + n)) を行う
 *
 *	@complexity	正確に N 回のスワップが行われる
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
BKSGE_CXX14_CONSTEXPR ForwardIterator2
swap_ranges(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2);

}	// namespace algorithm

using algorithm::swap_ranges;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/swap_ranges_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SWAP_RANGES_HPP
