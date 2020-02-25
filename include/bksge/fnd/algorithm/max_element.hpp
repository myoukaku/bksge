﻿/**
 *	@file	max_element.hpp
 *
 *	@brief	max_element の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_MAX_ELEMENT_HPP
#define BKSGE_FND_ALGORITHM_MAX_ELEMENT_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		[first, last)の範囲において、最大要素を指すイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *
 *	@param		first
 *	@param		last
 *
 *	@return		*j < *i の比較によって最大と判断された要素を指すイテレータ
 *
 *	@complexity	max((last - first) - 1, 0)回の比較を行う
 */
template <
	typename ForwardIterator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
max_element(ForwardIterator first, ForwardIterator last);

/**
 *	@brief		[first, last)の範囲において、最大要素を指すイテレータを取得する
 *
 *	@tparam		ForwardIterator
 *	@tparam		Compare
 *
 *	@param		first
 *	@param		last
 *	@param		comp
 *
 *	@return		comp(*j, *i) の比較によって最大と判断された要素を指すイテレータ
 *
 *	@complexity	max((last - first) - 1, 0)回の比較を行う
 */
template <
	typename ForwardIterator,
	typename Compare,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR ForwardIterator
max_element(ForwardIterator first, ForwardIterator last, Compare comp);

}	// namespace algorithm

using algorithm::max_element;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/max_element_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_MAX_ELEMENT_HPP