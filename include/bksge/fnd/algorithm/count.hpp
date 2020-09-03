/**
 *	@file	count.hpp
 *
 *	@brief	count の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COUNT_HPP
#define BKSGE_FND_ALGORITHM_COUNT_HPP

#include <bksge/fnd/iterator/iter_difference_t.hpp>
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
template <typename InputIterator, typename T>
BKSGE_CXX14_CONSTEXPR bksge::iter_difference_t<InputIterator>
count(InputIterator first, InputIterator last, T const& value);

}	// namespace algorithm

using algorithm::count;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/count_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COUNT_HPP
