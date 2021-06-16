/**
 *	@file	replace_copy.hpp
 *
 *	@brief	replace_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REPLACE_COPY_HPP
#define BKSGE_FND_ALGORITHM_REPLACE_COPY_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された値に一致する要素を指定された値に置き換え、その結果を出力の範囲へコピーする。
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		old_value
 *	@param		new_value
 *
 *	@require	*first と new_value は result へ書き込み可能でなければならない。
 *				また、[first,last) と [result,result + (last - first)) の範囲が重なっていてはならない。
 *
 *	@return		result + (last - first)
 *
 *	@effect		[result,result + (last - first)) 内のイテレータ i について、
 *				*(first + (i - result)) == old_value である場合は new_value が代入され、
 *				そうでない場合は *(first + (i - result)) が 代入される。
 *
 *	@complexity	正確に last - first 回の比較を行う
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename T
>
BKSGE_CXX14_CONSTEXPR OutputIterator 
replace_copy(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	T const& old_value,
	T const& new_value);

}	// namespace algorithm

using algorithm::replace_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/replace_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REPLACE_COPY_HPP
