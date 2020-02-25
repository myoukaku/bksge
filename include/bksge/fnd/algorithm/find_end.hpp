/**
 *	@file	find_end.hpp
 *
 *	@brief	find_end の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FIND_END_HPP
#define BKSGE_FND_ALGORITHM_FIND_END_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲の中から、特定のサブシーケンスを検索する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *
 *	@return		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *				0 以上 last2 - first2 未満の全ての整数 n について、
 *				それぞれ *(i + n) == *(first2 + n) であるようなサブシーケンスを探し、
 *				見つかった 最後の サブシーケンスの先頭のイテレータを返す。
 *				そのようなイテレータが見つからない、もしくは [first2,last2) が空である場合は last1 を返す。
 *
 *	@complexity	最大で (last2 - first2) * (last1 - first1 - (last2 - first2) + 1) 回の、
 *				対応する比較が適用される
 *
 *	@note		search() と find_end() は共にサブシーケンスを検索する関数だが、以下の点が異なる。
 *				・search() は見つかった最初のサブシーケンスを返すが
 *				  find_end() は見つかった最後のサブシーケンスを返す
 *				・[first2,last2) が空であるときに search() は first1 を返すが、find_end() は last1 を返す
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator1>::value &&
		bksge::is_forward_iterator<ForwardIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2);

/**
 *	@brief		範囲の中から、特定のサブシーケンスを検索する
 *
 *	@tparam		ForwardIterator1
 *	@tparam		ForwardIterator2
 *	@tparam		BinaryPredicate
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		pred
 *
 *	@return		[first1,last1 - (last2 - first2)) 内のイテレータ i があるとき、
 *				0 以上 last2 - first2 未満の全ての整数 n について、
 *				それぞれ pred(*(i + n), *(first2 + n)) != false であるようなサブシーケンスを探し、
 *				見つかった 最後の サブシーケンスの先頭のイテレータを返す。
 *				そのようなイテレータが見つからない、もしくは [first2,last2) が空である場合は last1 を返す。
 *
 *	@complexity	最大で (last2 - first2) * (last1 - first1 - (last2 - first2) + 1) 回の、
 *				対応する述語が適用される
 *
 *	@note		search() と find_end() は共にサブシーケンスを検索する関数だが、以下の点が異なる。
 *				・search() は見つかった最初のサブシーケンスを返すが
 *				  find_end() は見つかった最後のサブシーケンスを返す
 *				・[first2,last2) が空であるときに search() は first1 を返すが、find_end() は last1 を返す
 */
template <
	typename ForwardIterator1,
	typename ForwardIterator2,
	typename BinaryPredicate,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator1>::value &&
		bksge::is_forward_iterator<ForwardIterator2>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator1
find_end(
	ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	BinaryPredicate pred);

}	// namespace algorithm

using algorithm::find_end;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/find_end_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FIND_END_HPP
