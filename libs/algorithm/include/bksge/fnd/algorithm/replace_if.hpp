/**
 *	@file	replace_if.hpp
 *
 *	@brief	replace_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REPLACE_IF_HPP
#define BKSGE_FND_ALGORITHM_REPLACE_IF_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		条件を満たす要素を指定された値に置き換える
 *
 *	@tparam		ForwardIterator
 *	@tparam		Predicate
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		pred
 *	@param		new_value
 *
 *	@require	*first = new_value という式が有効でなければならない。
 *
 *	@effect		[first,last) 内のイテレータ i について、
 *				pred(*i) != false であるものは *i = new_value という式によって置き換えられる。
 *
 *	@complexity	正確に last - first 回の述語の適用を行う。
 */
template <
	typename ForwardIterator,
	typename Predicate,
	typename T
>
BKSGE_CXX14_CONSTEXPR void
replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, T const& new_value);

}	// namespace algorithm

using algorithm::replace_if;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/replace_if_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REPLACE_IF_HPP
