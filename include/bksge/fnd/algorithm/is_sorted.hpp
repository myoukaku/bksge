/**
 *	@file	is_sorted.hpp
 *
 *	@brief	is_sorted の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_IS_SORTED_HPP
#define BKSGE_FND_ALGORITHM_IS_SORTED_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		与えられた範囲がソート済みか判定する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		is_sorted_until(first, last) == last
 *
 *	@complexity	線形時間
 */
template <
	typename ForwardIterator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
is_sorted(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		与えられた範囲がソート済みか判定する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		is_sorted_until(first, last, comp) == last
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
BKSGE_CXX14_CONSTEXPR bool
is_sorted(ForwardIterator first, ForwardIterator last, Compare comp);

}	// namespace algorithm

using algorithm::is_sorted;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/is_sorted_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_IS_SORTED_HPP
