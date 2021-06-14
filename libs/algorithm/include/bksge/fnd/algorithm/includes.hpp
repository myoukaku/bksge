/**
 *	@file	includes.hpp
 *
 *	@brief	includes の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INCLUDES_HPP
#define BKSGE_FND_ALGORITHM_INCLUDES_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		2つのソート済み範囲において、一方の範囲の要素がもう一方の範囲に全て含まれているかを判定する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		[first2,last2) が empty であるか、
 *				[first2,last2) の全ての要素が [first1,last1) に含まれている場合は true、
 *				そうでない場合は false を返す。
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回比較する
 */
template <
	typename InputIterator1,
	typename InputIterator2
>
BKSGE_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2);

/**
 *	@brief		2つのソート済み範囲において、一方の範囲の要素がもう一方の範囲に全て含まれているかを判定する
 *
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		Compare
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		comp
 *
 *	@return		[first2,last2) が empty であるか、
 *				[first2,last2) の全ての要素が [first1,last1) に含まれている場合は true、
 *				そうでない場合は false を返す。
 *
 *	@complexity	最大で 2 * ((last1 - first1) + (last2 - first2)) - 1 回比較する
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename Compare
>
BKSGE_CXX14_CONSTEXPR bool
includes(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	Compare comp);

}	// namespace algorithm

using algorithm::includes;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/includes_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_INCLUDES_HPP
