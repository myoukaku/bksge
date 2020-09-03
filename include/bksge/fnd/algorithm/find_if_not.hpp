/**
 *	@file	find_if_not.hpp
 *
 *	@brief	find_if_not の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FIND_IF_NOT_HPP
#define BKSGE_FND_ALGORITHM_FIND_IF_NOT_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲の中から、指定された条件を満たさない最初の要素を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について、pred(*i) == false である最初のイテレータを返す。
 *				そのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	最大で last - first 回述語による比較を行う
 */
template <typename InputIterator, typename Predicate>
BKSGE_CXX14_CONSTEXPR InputIterator
find_if_not(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::find_if_not;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/find_if_not_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FIND_IF_NOT_HPP
