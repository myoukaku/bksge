/**
 *	@file	upper_bound.hpp
 *
 *	@brief	upper_bound の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_UPPER_BOUND_HPP
#define BKSGE_FND_ALGORITHM_UPPER_BOUND_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された要素より大きい値が現れる最初の位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	first、last は前方向イテレータの要件を満たすこと。
 *				[first,last) の要素 e は !(value < e) によって区分化されていること。
 *				つまり、!(value < e) が true となる全ての要素 e は、
 *				false となる全ての要素よりも左側（first に近い方）になければならない。
 *
 *	@return		[first, last] 内のイテレータ i のうち、以下の条件を満たす、最も右側（first から遠い方）のもの
 *				・[first, i) 内の全てのイテレータ j が !(value < *j) である
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <typename ForwardIterator, typename T>
BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(ForwardIterator first, ForwardIterator last, T const& value);

/**
 *	@brief		指定された要素より大きい値が現れる最初の位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *	@param		comp
 *
 *	@require	first、last は前方向イテレータの要件を満たすこと。
 *				comp は 2 引数の関数オブジェクトで、結果の型は bool 型に変換可能であること。
 *				また、引数に非 const の関数を適用しないこと。
 *				[first,last) の要素 e は !comp(value, e) によって区分化されていること。
 *				つまり、!comp(value, e) が true となる全ての要素 e は、
 *				false となる全ての要素よりも左側（first に近い方）になければならない。
 *
 *	@return		[first, last] 内のイテレータ i のうち、以下の条件を満たす、最も右側（first から遠い方）のもの
 *				・[first, i) 内の全てのイテレータ j が comp(value, *j) == false である
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <typename ForwardIterator, typename T, typename Compare>
BKSGE_CXX14_CONSTEXPR ForwardIterator
upper_bound(ForwardIterator first, ForwardIterator last, T const& value, Compare comp);

}	// namespace algorithm

using algorithm::upper_bound;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/upper_bound_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_UPPER_BOUND_HPP
