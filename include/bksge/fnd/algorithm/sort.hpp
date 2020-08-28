/**
 *	@file	sort.hpp
 *
 *	@brief	sort の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SORT_HPP
#define BKSGE_FND_ALGORITHM_SORT_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	N log N (N == last - first) 回の比較
 */
template <typename RandomAccessIterator>
BKSGE_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last);

/**
 *	@brief		範囲を並べ替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@require	RandomAccessIterator は ValueSwappable の要求を満たしている必要がある。
 *				*first の型は MoveConstructible と MoveAssignable の要件を満たしている必要がある。
 *
 *	@effect		[first,last) の範囲をソートする
 *
 *	@complexity	N log N (N == last - first) 回の比較
 */
template <typename RandomAccessIterator, typename Compare>
BKSGE_CXX14_CONSTEXPR void
sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);

}	// namespace algorithm

using algorithm::sort;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/sort_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SORT_HPP
