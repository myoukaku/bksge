/**
 *	@file	adjacent_difference.hpp
 *
 *	@brief	adjacent_difference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_ADJACENT_DIFFERENCE_HPP
#define BKSGE_FND_NUMERIC_ADJACENT_DIFFERENCE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace numeric
{

/**
 *	@brief		隣接する要素間の差を計算する。
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
 *	@require	InputIteratorが指す値の型が、MoveAssignableであり、*firstで初期化でき、result出力イテレータに書き込めること
 *				InputIteratorが指す値の型のオブジェクトaとbにおいて、式binary_op(b, a)の結果がresult出力イテレータに書き込めること
 *				binary_opの呼び出しが、範囲[first, last]および範囲[result, result + (last - first)]の要素変更、イテレータの無効化をしてはならない
 *
 *	@effect		*(result)   = *first;
 *				*(result+1) = *(first+1) - *(first);
 *				*(result+2) = *(first+2) - *(first+1);
 *				*(result+3) = *(first+3) - *(first+2);
 *				...
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に(last - first) - 1回だけbinary_opを適用する
 */
template <
	typename InputIterator,
	typename OutputIterator
>
BKSGE_CXX14_CONSTEXPR OutputIterator
adjacent_difference(
	InputIterator first,
	InputIterator last,
	OutputIterator result);

/**
 *	@overload
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename BinaryOperation
>
BKSGE_CXX14_CONSTEXPR OutputIterator
adjacent_difference(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	BinaryOperation binary_op);

}	// namespace numeric

using numeric::adjacent_difference;

}	// namespace bksge

#include <bksge/fnd/numeric/inl/adjacent_difference_inl.hpp>

#endif // BKSGE_FND_NUMERIC_ADJACENT_DIFFERENCE_HPP
