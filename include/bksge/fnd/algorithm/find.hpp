/**
 *	@file	find.hpp
 *
 *	@brief	find の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_FIND_HPP
#define BKSGE_FND_ALGORITHM_FIND_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された値を検索する
 *
 *	@tparam		InputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@return		[first,last) 内のイテレータ i について、*i == value であるような最初のイテレータを返す。
 *				そのようなイテレータが見つからなかった場合は last を返す。
 *
 *	@complexity	最大で last - first 回比較を行う
 */
template <
	typename InputIterator,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR InputIterator
find(InputIterator first, InputIterator last, T const& value);

}	// namespace algorithm

using algorithm::find;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/find_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_FIND_HPP
