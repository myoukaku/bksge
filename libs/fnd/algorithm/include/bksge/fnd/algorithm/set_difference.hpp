/**
 *	@file	set_difference.hpp
 *
 *	@brief	set_difference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SET_DIFFERENCE_HPP
#define BKSGE_FND_ALGORITHM_SET_DIFFERENCE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		2つのソート済み範囲の差集合を得る
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		OutputIterator
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *
 *	@require	結果の範囲は両方の入力の範囲と重なっていてはならない。
 *
 *	@effect		[first1,last1) から、[first2,last2) に存在していない要素を result へコピーする。
 *				構築された範囲はソートされている。
 *
 *	@return		構築された範囲の終端
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回の比較を行う
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator
>
OutputIterator
set_difference(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result);

/**
 *	@brief		2つのソート済み範囲の差集合を得る
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		OutputIterator
 *	@tparam		Compare
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *	@param		comp
 *
 *	@require	結果の範囲は両方の入力の範囲と重なっていてはならない。
 *
 *	@effect		[first1,last1) から、[first2,last2) に存在していない要素を result へコピーする。
 *				構築された範囲はソートされている。
 *
 *	@return		構築された範囲の終端
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回の比較を行う
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare
>
OutputIterator
set_difference(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	Compare comp);

}	// namespace algorithm

using algorithm::set_difference;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/set_difference_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SET_DIFFERENCE_HPP
