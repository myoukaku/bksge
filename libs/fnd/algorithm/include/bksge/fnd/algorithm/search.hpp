/**
 *	@file	search.hpp
 *
 *	@brief	search の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SEARCH_HPP
#define BKSGE_FND_ALGORITHM_SEARCH_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator1
 *	@tparam	ForwardIterator2
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *
 *	@return
 *		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *		0 以上 last2 - first2 未満の整数 n について、それぞれ *(i + n) == *(first2 + n)
 *		であるようなサブシーケンスを探し、見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last1 を返し、[first2,last2) が空である場合には first1 を返す。
 *
 *	@complexity	最大で (last1 - first1) * (last2 - first2) 回の、対応する比較が適用される
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2
>
BKSGE_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2);

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator1
 *	@tparam	ForwardIterator2
 *	@tparam	BinaryPredicate
 *
 *	@param	first1
 *	@param	last1
 *	@param	first2
 *	@param	last2
 *	@param	pred
 *
 *	@return
 *		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *		0 以上 last2 - first2 未満の整数 n について、それぞれ pred(*(i + n), *(first2 + n)) != false
 *		であるようなサブシーケンスを探し、見つかった最初のサブシーケンスの先頭のイテレータを返す。
 *		そのようなイテレータが見つからない場合は last1 を返し、[first2,last2) が空である場合には first1 を返す。
 *
 *	@complexity	最大で (last1 - first1) * (last2 - first2) 回の、対応する述語が適用される
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate
>
BKSGE_CXX14_CONSTEXPR ForwardIterator1
search(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred);

/**
 *	@brief	あるシーケンスの中から、特定のサブシーケンスを探す
 *
 *	@tparam	ForwardIterator
 *	@tparam	Searcher
 *
 *	@param	first
 *	@param	last
 *	@param	searcher
 *
 *	@return	searcher.operator() の結果を返す。
 *
 *	@complexity	searcher に依存する
 */
template <typename ForwardIterator, typename Searcher>
BKSGE_CXX14_CONSTEXPR ForwardIterator
search(
	ForwardIterator first,
	ForwardIterator last,
	Searcher const& searcher)
{
	return searcher(first, last).first;
}

}	// namespace algorithm

using algorithm::search;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/search_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SEARCH_HPP
