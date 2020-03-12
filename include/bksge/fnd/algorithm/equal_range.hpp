/**
 *	@file	equal_range.hpp
 *
 *	@brief	equal_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_EQUAL_RANGE_HPP
#define BKSGE_FND_ALGORITHM_EQUAL_RANGE_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		lower_bound()とupper_bound()の結果を組で取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@require	[first,last) の要素 e は e < value および !(value < e) によって区分化されていなければならない。
 *				また、[first, last) の要素 e は全て暗黙に、e < value が !(value < e) を意味している必要がある。
 *
 *	@return		make_pair(lower_bound(first, last, value), upper_bound(first, last, value))
 *
 *	@complexity	最大で 2 * log2(last - first) + O(1) 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR std::pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, T const& value);

/**
 *	@brief		lower_bound()とupper_bound()の結果を組で取得する
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
 *				また、[first, last) の要素 e は全て暗黙に、comp(e, value) が !comp(value, e) を意味している必要がある。
 *
 *	@return		make_pair(lower_bound(first, last, value, comp), upper_bound(first, last, value, comp))
 *
 *	@complexity	最大で 2 * log2(last - first) + O(1) 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR std::pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last, T const& value, Compare comp);

}	// namespace algorithm

using algorithm::equal_range;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/equal_range_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_EQUAL_RANGE_HPP
