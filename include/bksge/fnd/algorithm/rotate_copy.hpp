/**
 *	@file	rotate_copy.hpp
 *
 *	@brief	rotate_copy の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_ROTATE_COPY_HPP
#define BKSGE_FND_ALGORITHM_ROTATE_COPY_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		要素の並びを回転させ、その結果を出力の範囲へコピーする。
 *
 *	@tparam		ForwardIterator
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *	@param		result
 *
 *	@require	[first,last) と [result,result + (last - first)) の範囲は重なっていてはならない。
 *
 *	@effect		0 以上 last - first 未満の整数 i について、
 *				*(result + i) = *(first + (i + (middle - first)) % (last - first)) という操作によって
 *				[first,last) の範囲を [result,result + (last - first)) の範囲へコピーする
 *
 *	@return		result + (last - first)
 *
 *	@complexity	正確に last - first 回代入する。
 */
template <typename ForwardIterator, typename OutputIterator>
OutputIterator
rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result);
	
}	// namespace algorithm

using algorithm::rotate_copy;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/rotate_copy_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_ROTATE_COPY_HPP
