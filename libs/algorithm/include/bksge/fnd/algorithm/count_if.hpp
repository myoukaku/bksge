/**
 *	@file	count_if.hpp
 *
 *	@brief	count_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COUNT_IF_HPP
#define BKSGE_FND_ALGORITHM_COUNT_IF_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		条件を満たしている要素の数を数える
 *
 *	@tparam		InputIterator
 *	@tparam		Predicate
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *
 *	@return		[first,last) 内のイテレータ i について、pred(*i) != false であるイテレータの数を返す
 *
 *	@complexity	正確に last - first 回の述語の適用を行う
 */
template <typename InputIterator, typename Predicate>
BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<InputIterator>
count_if(InputIterator first, InputIterator last, Predicate pred);

}	// namespace algorithm

using algorithm::count_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/count_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COUNT_IF_HPP
