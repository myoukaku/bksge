﻿/**
 *	@file	sample.hpp
 *
 *	@brief	sample の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SAMPLE_HPP
#define BKSGE_FND_ALGORITHM_SAMPLE_HPP

#include <bksge/fnd/iterator/type_traits/is_forward_iterator.hpp>
#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		[first,last) から n 個の要素をランダムで選んで out に出力する
 *
 *	@tparam		PopulationIterator
 *	@tparam		SampleIterator
 *	@tparam		Distance
 *	@tparam		UniformRandomBitGenerator
 *
 *	@param		first
 *	@param		last
 *	@param		out
 *	@param		n
 *	@param		g
 *
 *	@require	・PopulationIterator は InputIterator の要件を満たす必要がある
 *				・SampleIterator は OutputIterator の要件を満たす必要がある
 *				・PopulationIterator が ForwardIterator の要件を満たさないとき、
 *				　SampleIterator は RandomAccessIterator の要件を満たす必要がある
 *				・PopulationIterator の value_type は out に書き込み可能でなければならない
 *				・Distance は整数型でなければならない
 *				・remove_reference_t<UniformRandomBitGenerator> は UniformRandomBitGenerator の要件を満たし、
 *				　かつ Distance に変換可能でなければならない
 *
 *	@return		出力後のout
 *
 *	@complexity	distance(first, last) に比例
 */
template <
	typename PopulationIterator,
	typename SampleIterator,
	typename Distance,
	typename UniformRandomBitGenerator,
	typename = bksge::enable_if_t<
		bksge::is_forward_iterator<PopulationIterator>::value ||
		bksge::is_random_access_iterator<SampleIterator>::value
	>,
	typename = bksge::enable_if_t<
		std::is_integral<Distance>::value
	>
>
SampleIterator
sample(
	PopulationIterator first,
	PopulationIterator last,
	SampleIterator out,
	Distance n,
	UniformRandomBitGenerator&& g);

}	// namespace algorithm

using algorithm::sample;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/sample_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SAMPLE_HPP