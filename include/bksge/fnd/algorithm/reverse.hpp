/**
 *	@file	reverse.hpp
 *
 *	@brief	reverse の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REVERSE_HPP
#define BKSGE_FND_ALGORITHM_REVERSE_HPP

#include <bksge/fnd/iterator/type_traits/is_bidirectional_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		要素の並びを逆にする。
 *
 *	@tparam		BidirectionalIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@require	*first は Swappable でなければならない
 *
 *	@effect		0 以上 (last - first) / 2 未満の整数 i について、
 *				iter_swap(first + i, (last - i) - 1) を行う
 *
 *	@complexity	正確に (last - first) / 2 回 swap する
 */
template <
	typename BidirectionalIterator,
	typename = bksge::enable_if_t<
		bksge::is_bidirectional_iterator<BidirectionalIterator>::value
	>
>
void
reverse(BidirectionalIterator first, BidirectionalIterator last);

}	// namespace algorithm

using algorithm::reverse;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/reverse_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REVERSE_HPP
