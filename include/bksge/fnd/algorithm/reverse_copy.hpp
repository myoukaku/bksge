/**
 *	@file	reverse_copy.hpp
 *
 *	@brief	reverse_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REVERSE_COPY_HPP
#define BKSGE_FND_ALGORITHM_REVERSE_COPY_HPP

#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		要素の並びを逆にし、その結果を出力の範囲へコピーする
 *
 *	@tparam		BidirectionalIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		last
 *	@param		result
 *
 *	@require	[first,last) と [result,result+(last-first)) は領域が重なっていてはならない。
 *
 *	@effect		0 以上 last - first 未満の整数 i について、
 *				*(result + (last - first) -1 - i) = *(first + i) を行うことで、
 *				[first,last) の範囲を [result,result+(last-first)) へコピーする。
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に last - first 回代入する
 */
template <
	typename BidirectionalIterator,
	typename OutputIterator,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR OutputIterator
reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result);

}	// namespace algorithm

using algorithm::reverse_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/reverse_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REVERSE_COPY_HPP
