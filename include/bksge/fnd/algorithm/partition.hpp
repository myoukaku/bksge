/**
 *	@file	partition.hpp
 *
 *	@brief	partition の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PARTITION_HPP
#define BKSGE_FND_ALGORITHM_PARTITION_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲を条件によって区分化する。
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	ForwardIterator は ValueSwappable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) 内にある pred を満たす全ての要素を、
 *				pred を満たさない全ての要素より前に移動させる。
 *
 *	@return		[first,i) 内にあるイテレータ j について pred(*j) != false を満たし、
 *				[i,last) 内にあるイテレータ k について pred(*k) == false を満たすような、
 *				イテレータ i を返す。
 *				つまり、区分化された境界を指すイテレータを返す。
 *
 *	@complexity	ForwardIterator が BidirectionalIterator の要求を満たしている場合、
 *				最大で (last - first) / 2 回 swap される。
 *				そうでない場合、最大で last - first 回 swap される。
 *				正確に last - first 回述語が適用される。
 */
template <
	typename ForwardIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
partition(ForwardIterator first, ForwardIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::partition;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/partition_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PARTITION_HPP
