/**
 *	@file	inplace_merge.hpp
 *
 *	@brief	inplace_merge の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_INPLACE_MERGE_HPP
#define BKSGE_FND_ALGORITHM_INPLACE_MERGE_HPP

#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		2つの連続したソート済み範囲をマージする
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *
 *	@require	[first,middle) と [middle,last) の範囲はそれぞれ operator< でソートされていること。
 *				BidirectionalIterator は ValueSwappable の要件を満たしていること。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしていること。
 *
 *	@effect		[first,middle), [middle,last) という、連続した２つの範囲をマージし、結果を [first,last) へ格納する。
 *				結果の範囲 [first,last) は昇順になる。
 *				つまり、first を除く [first,last) 内の全てのイテレータ i について、
 *				*i < *(i - 1) が false になる。
 *
 *	@complexity	N log(N) （N は last - first）回程度比較する
 */
template <
	typename BidirectionalIterator,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator>::value
	>
>
void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last);

/**
 *	@brief		2つの連続したソート済み範囲をマージする
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *
 *	@require	[first,middle) と [middle,last) の範囲はそれぞれ comp でソートされていること。
 *				BidirectionalIterator は ValueSwappable の要件を満たしていること。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしていること。
 *
 *	@effect		[first,middle), [middle,last) という、連続した２つの範囲をマージし、結果を [first,last) へ格納する。
 *				結果の範囲 [first,last) は昇順になる。
 *				つまり、first を除く [first,last) 内の全てのイテレータ i について、
 *				comp(*i, *(i - 1)) が false になる。
 *
 *	@complexity	N log(N) （N は last - first）回程度比較する
 */
template <
	typename BidirectionalIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator>::value
	>
>
void
inplace_merge(
	BidirectionalIterator first,
	BidirectionalIterator middle,
	BidirectionalIterator last,
	Compare comp);

}	// namespace algorithm

using algorithm::inplace_merge;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/inplace_merge_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_INPLACE_MERGE_HPP
