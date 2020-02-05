/**
 *	@file	adjacent_find.hpp
 *
 *	@brief	adjacent_find の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_ADJACENT_FIND_HPP
#define BKSGE_FND_ALGORITHM_ADJACENT_FIND_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		隣接する要素で条件を満たしている最初の要素を検索する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		[first,last) 内にあるイテレータ i について、
 *				*i == *(i + 1) であるような最初のイテレータを返す。
 *				もしそのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	与えられたシーケンスが空でない場合、
 *				正確に min((i - first) + 1, (last - first) - 1) 回
 *				（i は adjacent_find の戻り値）の比較が適用される
 */
template <
	typename ForwardIterator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		隣接する要素で条件を満たしている最初の要素を検索する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内にあるイテレータ i について、
 *				pred(*i, *(i + 1)) != false であるような最初のイテレータを返す。
 *				もしそのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	与えられたシーケンスが空でない場合、
 *				正確に min((i - first) + 1, (last - first) - 1) 回
 *				（i は adjacent_find の戻り値）の述語が適用される
 */
template <
	typename ForwardIterator,
	typename BinaryPredicate,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred);

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/adjacent_find_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_ADJACENT_FIND_HPP
