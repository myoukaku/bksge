/**
 *	@file	any_of.hpp
 *
 *	@brief	any_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_ANY_OF_HPP
#define BKSGE_FND_ALGORITHM_ANY_OF_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		範囲のいずれかの要素が条件を満たすかを判定する
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について
 *				pred(*i) が true になるような要素があればtrueを返し、
 *				そうでなければfalseを返す。 
 *				[first,last)の範囲が空の場合はfalseを返す。
 *
 *	@complexity	最大で last - first 回 pred を実行する。
 */
template <
	typename InputIterator,
	typename Predicate
>
BKSGE_CXX14_CONSTEXPR bool
any_of(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::any_of;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/any_of_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_ANY_OF_HPP
