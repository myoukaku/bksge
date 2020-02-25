/**
 *	@file	is_sorted_until.hpp
 *
 *	@brief	is_sorted_until の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_SORTED_UNTIL_HPP
#define BKSGE_FND_ALGORITHM_IS_SORTED_UNTIL_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		ソート済みか判定し、ソートされていない位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		distance(first, last) < 2 なら last を返す。
 *				そうでない場合、[first,last] の中でソートされている範囲を [first,i) としたとき、
 *				そのイテレータ i を返す。
 *
 *	@complexity	線形時間
 */
template <
	typename ForwardIterator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
is_sorted_until(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		ソート済みか判定し、ソートされていない位置のイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		distance(first, last) < 2 なら last を返す。
 *				そうでない場合、[first,last] の中でソートされている範囲を [first,i) としたとき、
 *				そのイテレータ i を返す。
 *
 *	@complexity	線形時間
 */
template <
	typename ForwardIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
is_sorted_until(ForwardIterator first, ForwardIterator last, Compare comp);

}	// namespace algorithm

using algorithm::is_sorted_until;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_sorted_until_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_SORTED_UNTIL_HPP
