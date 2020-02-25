/**
 *	@file	find_if.hpp
 *
 *	@brief	find_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FIND_IF_HPP
#define BKSGE_FND_ALGORITHM_FIND_IF_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲の中から、指定された条件を満たす最初の要素を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について、pred(*i) != false である最初のイテレータを返す。
 *				そのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	最大で last - first 回述語による比較を行う
 */
template <
	typename InputIterator,
	typename Predicate,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR InputIterator
find_if(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::find_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/find_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FIND_IF_HPP
