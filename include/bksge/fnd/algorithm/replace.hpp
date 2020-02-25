/**
 *	@file	replace.hpp
 *
 *	@brief	replace の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_REPLACE_HPP
#define BKSGE_FND_ALGORITHM_REPLACE_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された値と一致する要素を指定された値に置き換える。
 *
 *	@tparam		ForwardIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		old_value
 *	@param		new_value
 *
 *	@require	*first = new_value という式が有効でなければならない。
 *
 *	@effect		[first,last) 内のイテレータ i について、
 *				*i == old_value であるものは *i = new_value という式によって置き換えられる。
 *
 *	@complexity	正確に last - first 回の比較を行う
 */
template <
	typename ForwardIterator,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<ForwardIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR void
replace(ForwardIterator first, ForwardIterator last, T const& old_value, T const& new_value);

}	// namespace algorithm

using algorithm::replace;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/replace_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_REPLACE_HPP
