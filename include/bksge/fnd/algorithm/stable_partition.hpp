/**
 *	@file	stable_partition.hpp
 *
 *	@brief	stable_partition の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_STABLE_PARTITION_HPP
#define BKSGE_FND_ALGORITHM_STABLE_PARTITION_HPP

#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲を相対順序を保ちながら条件によって区分化する。
 *
 *	@tparam		BidirectionalIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@require	BidirectionalIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) 内にある pred を満たす全ての要素を、pred を満たさない全ての要素より前に移動させる。
 *
 *	@return		[first,i) 内にあるイテレータ j について pred(*j) != false を満たし、
 *				[i,last) 内にあるイテレータ k について pred(*k) == false を満たすような、
 *				イテレータ i を返す。
 *				つまり、区分化された境界を指すイテレータを返す。
 *
 *	@complexity	最大で (last - first) * log(last - first) 回 swap が行われる。
 *				正確に last - first 回述語が適用される。
 *
 *	@note		条件を満たす・満たさない両グループ内での要素間の相対順序は保たれる。
 */
template <
	typename BidirectionalIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator>::value
	>
>
BidirectionalIterator
stable_partition(
	BidirectionalIterator first,
	BidirectionalIterator last,
	Predicate pred);
  
}	// namespace algorithm

using algorithm::stable_partition;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/stable_partition_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_STABLE_PARTITION_HPP
