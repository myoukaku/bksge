/**
 *	@file	merge.hpp
 *
 *	@brief	merge の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MERGE_HPP
#define BKSGE_FND_ALGORITHM_MERGE_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		2つのソート済み範囲をマージする。
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
 *	@require	[first1,last1) と [first2,last2) は operator< でソートされていること。
 *				結果の範囲と入力の範囲は重なっていてはならない。
 *
 *	@effect		[first1,last1) と [first2,last2) の２つの要素を全て [result,result_last) へコピーする。
 *				その際に、is_sorted(result, result_last) の条件を満たすようにコピーする
 *				（result_last は result + (last1 - first1) + (last2 - first2) とする）。
 *
 *	@return		result + (last1 - first1) + (last2 - first2)
 *
 *	@complexity	最大で (last1 - first1) + (last2 - first2) - 1 回比較する。
 *
 *	@note		この操作は安定である。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
OutputIterator
merge(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result);

/**
 *	@brief		2つのソート済み範囲をマージする。
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
 *	@require	[first1,last1) と [first2,last2) は comp でソートされていること。
 *				結果の範囲と入力の範囲は重なっていてはならない。
 *
 *	@effect		[first1,last1) と [first2,last2) の２つの要素を全て [result,result_last) へコピーする。
 *				その際に、is_sorted(result, result_last, comp) の条件を満たすようにコピーする
 *				（result_last は result + (last1 - first1) + (last2 - first2) とする）。
 *
 *	@return		result + (last1 - first1) + (last2 - first2)
 *
 *	@complexity	最大で (last1 - first1) + (last2 - first2) - 1 回比較する。
 *
 *	@note		この操作は安定である。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
OutputIterator
merge(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	Compare comp);

}	// namespace algorithm

using algorithm::merge;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/merge_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MERGE_HPP
