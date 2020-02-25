/**
 *	@file	stable_sort.hpp
 *
 *	@brief	stable_sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_STABLE_SORT_HPP
#define BKSGE_FND_ALGORITHM_STABLE_SORT_HPP

#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲を安定ソートで並べ替える
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	最大で N log^2(N) （N == last - first）回の比較を行う。
 *				ただし、十分なメモリがあれば N log(N) になる。
 */
template <
	typename RandomAccessIterator,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
stable_sort(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		範囲を安定ソートで並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	最大で N log^2(N) （N == last - first）回の比較を行う。
 *				ただし、十分なメモリがあれば N log(N) になる。
 */
template <
	typename RandomAccessIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
stable_sort(
	RandomAccessIterator first,
	RandomAccessIterator last,
	Compare comp);

}	// namespace algorithm

using algorithm::stable_sort;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/stable_sort_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_STABLE_SORT_HPP
