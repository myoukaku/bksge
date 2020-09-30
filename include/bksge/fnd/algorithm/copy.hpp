/**
 *	@file	copy.hpp
 *
 *	@brief	copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COPY_HPP
#define BKSGE_FND_ALGORITHM_COPY_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された範囲の要素をコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	result は [first,last) の範囲に含まれてはならない
 *
 *	@return		result + (last - first)
 *
 *	@effect		[first,last) 内の要素を、それぞれ [result,result + (last - first)) へコピーする。
 *				コピーは first から順番に行い、0 以上 last - first 未満であるそれぞれの n について、
 *				*(result + n) = *(first + n) を行う
 *
 *	@complexity	正確に last - first 回代入が行われる。
 */
template <
	typename InputIterator,
	typename OutputIterator
>
BKSGE_CXX14_CONSTEXPR OutputIterator
copy(InputIterator first, InputIterator last, OutputIterator result);

/**
 *	@brief
 */
template <
	typename InputIterator,
	typename OutputIterator
>
BKSGE_CXX14_CONSTEXPR OutputIterator
copy(
	InputIterator  first,        InputIterator  last,
	OutputIterator result_first, OutputIterator result_last);

}	// namespace algorithm

using algorithm::copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COPY_HPP
