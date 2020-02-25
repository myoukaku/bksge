/**
 *	@file	transform.hpp
 *
 *	@brief	transform の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_TRANSFORM_HPP
#define BKSGE_FND_ALGORITHM_TRANSFORM_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		全ての要素に関数を適用する
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		UnaryOperation
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		unary_op
 *
 *	以下、last - first を N とおく。
 *
 *	@return		result + N
 *
 *	@require	unary_op は、[first, last], [result, result + N] 内のイテレータや
 *				subrange を無効にしたり、要素を書き換えてはならない。
 *
 *	@effect		[result, result + N) 内のイテレータ i の要素に、
 *				それぞれ unary_op(*(first + (i - result))) を代入する
 *
 *	@complexity	正確に N 回の unary_op の適用が行われる。
 *
 *	@note		result は first と同じであっても構わない。
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename UnaryOperation,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator first, InputIterator last,
	OutputIterator result,
	UnaryOperation unary_op);

/**
 *	@brief		全ての要素に関数を適用する
 *
 *	@tparam		OutputRange
 *	@tparam		InputIterator1
 *	@tparam		InputIterator2
 *	@tparam		BinaryOperation
 *
 *	@param		first1
 *	@param		last1
 *	@param		first2
 *	@param		last2
 *	@param		result
 *	@param		binary_op
 *
 *	以下、min(last1 - first1, last2 - first2) を N とおく。
 *
 *	@return		result + N
 *
 *	@require	binary_op は、[first1, last1], [first2, last2], [result, result + N]
 *				内のイテレータや subrange を無効にしたり、要素を書き換えてはならない。
 *
 *	@effect		[result, result + N) 内のイテレータ i の要素に、
 *				それぞれ binary_op(*(first1 + (i - result)), *(first2 + (i - result))) を代入する。
 *
 *	@complexity	正確に N 回の unary_op の適用が行われる。
 *
 *	@note		result は first1 や first2 と同じであっても構わない。
 */
template <
	typename InputIterator1,
	typename InputIterator2,
	typename OutputIterator,
	typename BinaryOperation,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator1>::value &&
		bksge::is_input_iterator<InputIterator2>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
transform(
	InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2,
	OutputIterator result,
	BinaryOperation binary_op);

}	// namespace algorithm

using algorithm::transform;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/transform_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_TRANSFORM_HPP
