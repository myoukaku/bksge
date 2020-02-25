/**
 *	@file	none_of.hpp
 *
 *	@brief	none_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_NONE_OF_HPP
#define BKSGE_FND_ALGORITHM_NONE_OF_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲の全ての要素が条件を満たさないかを判定する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) が空であったり、[first,last) 内の全てのイテレータ i について
 *				 pred(*i) が false である場合は true を返し、そうでない場合は false を返す。
 *
 *	@complexity	最大で last - first 回 pred を実行する。
 */
template <
	typename InputIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bool
none_of(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::none_of;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/none_of_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_NONE_OF_HPP
