/**
 *	@file	partial_sum.hpp
 *
 *	@brief	partial_sum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_PARTIAL_SUM_HPP
#define BKSGE_FND_NUMERIC_PARTIAL_SUM_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace numeric
{

/**
 *	@brief		範囲の値の部分和を計算する。
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		BinaryOperation
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		binary_op
 *
 *	@require	InputIteratorの値型は、*firstの型から構築可能でなければならない
 *				binary_opの戻り値が、InputIteratorの値型に変換可能でなければならない
 *				binary_opの戻り値が、result出力イテレータに書き込めなければならない
 *				binary_opは入力範囲[first, last]および出力範囲[result, result + (last - first)]
 *				の要素を変更してはならず、そのイテレータと部分範囲を無効化してはならない
 *
 *	@effect		*(result)   = *first;
 *				*(result+1) = *first + *(first+1);
 *				*(result+2) = *first + *(first+1) + *(first+2);
 *				*(result+3) = *first + *(first+1) + *(first+2) + *(first+3);
 *				...
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に(last - first) - 1回だけbinary_opを適用する
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
partial_sum(
	InputIterator first,
	InputIterator last,
	OutputIterator result);

/**
 *	@overload
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
partial_sum(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op);

}	// namespace numeric

using numeric::partial_sum;

}	// namespace bksge

#include <bksge/fnd/numeric/inl/partial_sum_inl.hpp>

#endif // BKSGE_FND_NUMERIC_PARTIAL_SUM_HPP
