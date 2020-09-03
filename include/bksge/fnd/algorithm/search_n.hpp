/**
 *	@file	search_n.hpp
 *
 *	@brief	search_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SEARCH_N_HPP
#define BKSGE_FND_ALGORITHM_SEARCH_N_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator
 *	@tparam	Size
 *	@tparam	T
 *
 *	@param	first
 *	@param	last
 *	@param	count
 *	@param	value
 *
 *	@require	Sizeは整数型に変換できる型である必要がある。
 *
 *	@return
 *		[first,last-count) 内のイテレータ i があるとき、0 以上 count 未満の整数 n について、
 *		それぞれ *(i + n) == value であるようなサブシーケンスを探し、
 *		見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last を返す。
 *
 *	@complexity	最大で last - first 回の対応する比較が適用される。
 */
template <
	typename ForwardIterator,
	typename Size,
	typename T
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value);

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator
 *	@tparam	Size
 *	@tparam	T
 *	@tparam	BinaryPredicate
 *
 *	@param	first
 *	@param	last
 *	@param	count
 *	@param	value
 *	@param	pred
 *
 *	@require	Sizeは整数型に変換できる型である必要がある。
 *
 *	@return
 *		[first,last-count) 内のイテレータ i があるとき、0 以上 count 未満の整数 n について、
 *		それぞれ pred(*(i + n),value) != false であるようなサブシーケンスを探し、
 *		見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last を返す。
 *
 *	@complexity	最大で last - first 回の対応する述語が適用される。
 */
template <
	typename ForwardIterator,
	typename Size,
	typename T,
	typename BinaryPredicate
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
search_n(
	ForwardIterator first,
	ForwardIterator last,
	Size count,
	T const& value,
	BinaryPredicate pred);

}	// namespace algorithm

using algorithm::search_n;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/search_n_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SEARCH_N_HPP
