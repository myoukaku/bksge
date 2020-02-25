/**
 *	@file	replace_copy_if.hpp
 *
 *	@brief	replace_copy_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REPLACE_COPY_IF_HPP
#define BKSGE_FND_ALGORITHM_REPLACE_COPY_IF_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		条件を満たす要素を指定された値に置き換え、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		Predicate
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		pred
 *	@param		new_value
 *
 *	@require	*first と new_value は result へ書き込み可能でなければならない。
 *				また、[first,last) と [result,result + (last - first)) の範囲が重なっていてはならない。
 *
 *	@return		result + (last - first)
 *
 *	@effect		[result,result + (last - first)) 内のイテレータ i について、
 *				pred(*(first + (i - result))) != false である場合は new_value が代入され、
 *				そうでない場合は *(first + (i - result)) が 代入される。
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename Predicate,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
replace_copy_if(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	Predicate pred,
	T const& new_value);

}	// namespace algorithm

using algorithm::replace_copy_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/replace_copy_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REPLACE_COPY_IF_HPP
