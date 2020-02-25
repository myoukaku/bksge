﻿/**
 *	@file	copy_n.hpp
 *
 *	@brief	copy_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_COPY_N_HPP
#define BKSGE_FND_ALGORITHM_COPY_N_HPP

#include <bksge/fnd/iterator/type_traits/is_input_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		指定された数の要素をコピーする
 *
 *	@tparam		InputIterator
 *	@tparam		Size
 *	@tparam		OutputIterator
 *
 *	@param		first
 *	@param		n
 *	@param		result
 *
 *	@return		result + n
 *
 *	@effect		0 以上 n 未満であるそれぞれの i について、*(result + i) = *(first + i) を行う。
 *
 *	@complexity	正確に n 回代入が行われる。
 */
template <
	typename InputIterator, typename Size, typename OutputIterator,
	typename = bksge::enable_if_t<
		bksge::is_input_iterator<InputIterator>::value &&
		bksge::is_iterator<OutputIterator>::value
	>
>
OutputIterator
copy_n(InputIterator first, Size n, OutputIterator result);

}	// namespace algorithm

using algorithm::copy_n;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/copy_n_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_COPY_N_HPP
