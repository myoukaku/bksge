/**
 *	@file	count.hpp
 *
 *	@brief	count の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COUNT_HPP
#define BKSGE_FND_ALGORITHM_COUNT_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/iterator_difference_type.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された値と等値な要素の数を数える
 *
 *	@tparam		InputIterator
 *	@tparam		T
 *
 *	@param		first
 *	@param		last
 *	@param		value
 *
 *	@return		[first,last) 内のイテレータ i について、*i == value であるイテレータの数を返す
 *
 *	@complexity	正確に last - first 回の比較を行う
 */
template <
	typename InputIterator,
	typename T,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value
	>
>
BKSGE_CXX14_CONSTEXPR bksge::iterator_difference_type<InputIterator>
count(InputIterator first, InputIterator last, T const& value);

}	// namespace algorithm

using algorithm::count;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/count_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COUNT_HPP
