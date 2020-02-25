/**
 *	@file	unique_copy.hpp
 *
 *	@brief	unique_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_UNIQUE_COPY_HPP
#define BKSGE_FND_ALGORITHM_UNIQUE_COPY_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		重複した要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	比較関数は等価関係を持っていなければならない。
 *				[first,last) と [result,result + (last - first)) は重なっていてはならない。
 *				*result = *first は有効な式でなければならない。
 *				InputIterator と OutputIterator のどちらも forward iterator の要求を満たしていない場合、
 *				InputIterator の value type は CopyConstructible かつ CopyAssignable でなければならない。
 *				そうでない場合は CopyConstructible は要求されない。
 *
 *	@effect		[first,last) 内のイテレータ i について、*(i - 1) == *i
 *				による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭を result へコピーする。
 *
 *	@return		結果の範囲の終端を返す。
 *
 *	@complexity	[first,last) が空の範囲でない場合、正確に last - first - 1 回の比較を行う
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
unique_copy(InputIterator first, InputIterator last, OutputIterator result);

/**
 *	@brief		重複した要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		BinaryPredicate
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		pred
 *
 *	@require	比較関数は等価関係を持っていなければならない。
 *				[first,last) と [result,result + (last - first)) は重なっていてはならない。
 *				*result = *first は有効な式でなければならない。
 *				InputIterator と OutputIterator のどちらも forward iterator の要求を満たしていない場合、
 *				InputIterator の value type は CopyConstructible かつ CopyAssignable でなければならない。
 *				そうでない場合は CopyConstructible は要求されない。
 *
 *	@effect		[first,last) 内のイテレータ i について、pred(*(i - 1), *i) != false
 *				による等値の比較によって連続したグループに分け、
 *				それぞれのグループの先頭を result へコピーする。
 *
 *	@return		結果の範囲の終端を返す。
 *
 *	@complexity	[first,last) が空の範囲でない場合、正確に last - first - 1 回の述語の適用を行う
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryPredicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
unique_copy(InputIterator first, InputIterator last, OutputIterator result, BinaryPredicate pred);

}	// namespace algorithm

using algorithm::unique_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/unique_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_UNIQUE_COPY_HPP
