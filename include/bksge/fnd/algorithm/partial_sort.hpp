/**
 *	@file	partial_sort.hpp
 *
 *	@brief	partial_sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_PARTIAL_SORT_HPP
#define BKSGE_FND_ALGORITHM_PARTIAL_SORT_HPP

#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲を部分的にソートし、先頭N個を並んだ状態にする。
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、middle - first 個の要素を
 *				ソート済みの状態で [first,middle) に配置する。
 *				残りの [middle,last) にある要素は unspecified order に配置される。
 *
 *	@complexity	ほぼ (last - first) * log(middle - first) 回の比較を行う
 */
template <
	typename RandomAccessIterator,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last);

/**
 *	@brief		範囲を部分的にソートし、先頭N個を並んだ状態にする。
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		middle
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) にある要素の中から、middle - first 個の要素を
 *				ソート済みの状態で [first,middle) に配置する。
 *				残りの [middle,last) にある要素は unspecified order に配置される。
 *
 *	@complexity	ほぼ (last - first) * log(middle - first) 回の比較を行う
 */
template <
	typename RandomAccessIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
partial_sort(
	RandomAccessIterator first,
	RandomAccessIterator middle,
	RandomAccessIterator last,
	Compare comp);

}	// namespace algorithm

using algorithm::partial_sort;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/partial_sort_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_PARTIAL_SORT_HPP
