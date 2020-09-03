/**
 *	@file	partition_point.hpp
 *
 *	@brief	partition_point の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PARTITION_POINT_HPP
#define BKSGE_FND_ALGORITHM_PARTITION_POINT_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲から条件によって区分化されている位置を得る。
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	ForwardIterator の value type は Predicate の argument type へ変換可能でなければならない。
 *				[first,last) は pred によって区分化されていなければならない。
 *				つまり、pred を満たす全ての要素が、pred を満たさない全ての要素より前に出現してなければならない。
 *
 *	@return		all_of(first, mid, pred) と none_of(mid, last, pred) が
 *				true であるようなイテレータ mid を返す。
 *
 *	@complexity	O(log(last - first)) のオーダーで pred が適用される。
 */
template <typename ForwardIterator, typename Predicate>
BKSGE_CXX14_CONSTEXPR ForwardIterator
partition_point(ForwardIterator first, ForwardIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::partition_point;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/partition_point_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PARTITION_POINT_HPP
