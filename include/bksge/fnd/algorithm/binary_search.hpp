/**
 *	@file	binary_search.hpp
 *
 *	@brief	binary_search の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_BINARY_SEARCH_HPP
#define BKSGE_FND_ALGORITHM_BINARY_SEARCH_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		二分探索法による検索を行う
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	[first,last) の要素 e は e < value および !(value < e) によって区分化されていなければならない。
 *				また、[first, last) の全ての要素 e は、e < value であれば !(value < e) である必要がある。
 *
 *	@return		[first,last) 内のイテレータ i について、
 *				!(*i < value) && !(value < *i) であるようなイテレータが見つかった場合は true を返す。
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
binary_search(ForwardIterator first, ForwardIterator last, T const& value);

/**
 *	@brief		二分探索法による検索を行う
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *	@param		comp
 *
 *	@require	[first,last) の要素 e は comp(e, value) および !comp(value, e) によって区分化されていなければならない。
 *				また、[first, last) の全ての要素 e は、comp(e, value) であれば !comp(value, e) である必要がある。
 *
 *	@return		[first,last) 内のイテレータ i について、
 *				comp(*i, value) == false && comp(value, *i) == false であるようなイテレータが見つかった場合は true を返す。
 *
 *	@complexity	最大で log2(last - first) + O(1) 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
binary_search(ForwardIterator first, ForwardIterator last, T const& value, Compare comp);

}	// namespace algorithm

using algorithm::binary_search;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/binary_search_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_BINARY_SEARCH_HPP
