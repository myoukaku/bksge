/**
 *	@file	remove_copy.hpp
 *
 *	@brief	remove_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REMOVE_COPY_HPP
#define BKSGE_FND_ALGORITHM_REMOVE_COPY_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief	指定された要素を取り除き、その結果を出力の範囲へコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		OutputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *	@param		value
 *
 *	@require	[first,last) と [result,result + (last - first) は重なってはならない。
 *				*result = *first という式が有効でなければならない。
 *
 *	@return		実行結果の範囲の終端を返す
 *
 *	@effect		[first,last) 内にあるイテレータ i について、
 *				*i == value でない要素を result へコピーする
 *
 *	@complexity	正確に last - first 回の比較を行う
 *
 *	@note		安定。
 */
template <
	typename InputIterator,
	typename OutputIterator,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
remove_copy(InputIterator first, InputIterator last, OutputIterator result, T const& value);

}	// namespace algorithm

using algorithm::remove_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/remove_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REMOVE_COPY_HPP
