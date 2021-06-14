/**
 *	@file	partial_sort_copy.hpp
 *
 *	@brief	partial_sort_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PARTIAL_SORT_COPY_HPP
#define BKSGE_FND_ALGORITHM_PARTIAL_SORT_COPY_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲を部分的にソートした結果を他の範囲にコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result_first
 *	@param		result_last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*result_first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、
 *				min(last - first, result_last - result_first) 個の要素をソート済みの状態で
 *				[result_first,result_first + min(last - first, result_last - result_first)) に配置する。
 *
 *	@return		result_last と result_first + (last - first) で小さい方が返される
 *
 *	@complexity	ほぼ (last - first) * log(min(last - first, result_last - result_- first)) 回の比較を行う
 */
template <
	typename InputIterator,
	typename RandomAccessIterator
>
BKSGE_CXX14_CONSTEXPR RandomAccessIterator
partial_sort_copy(
	InputIterator        first,        InputIterator        last,
	RandomAccessIterator result_first, RandomAccessIterator result_last);

/**
 *	@brief		範囲を部分的にソートした結果を他の範囲にコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		result_first
 *	@param		result_last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*result_first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、
 *				min(last - first, result_last - result_first) 個の要素をソート済みの状態で
 *				[result_first,result_first + min(last - first, result_last - result_first)) に配置する。
 *
 *	@return		result_last と result_first + (last - first) で小さい方が返される
 *
 *	@complexity	ほぼ (last - first) * log(min(last - first, result_last - result_- first)) 回の比較を行う
 */
template <
	typename InputIterator,
	typename RandomAccessIterator,
	typename Compare
>
BKSGE_CXX14_CONSTEXPR RandomAccessIterator
partial_sort_copy(
	InputIterator        first,        InputIterator        last,
	RandomAccessIterator result_first, RandomAccessIterator result_last,
	Compare comp);

}	// namespace algorithm

using algorithm::partial_sort_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/partial_sort_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PARTIAL_SORT_COPY_HPP
