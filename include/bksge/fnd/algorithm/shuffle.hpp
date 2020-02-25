/**
 *	@file	shuffle.hpp
 *
 *	@brief	shuffle の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_SHUFFLE_HPP
#define BKSGE_FND_ALGORITHM_SHUFFLE_HPP

#include <bksge/fnd/iterator/type_traits/is_random_access_iterator.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace algorithm
{

/**
 *	@brief		[first,last) のそれぞれの要素を同じ確率で並び替える
 *
 *	@tparam		RandomAccessIterator
 *	@tparam		UniformRandomNumberGenerator
 *
 *	@param		first
 *	@param		last
 *	@param		g
 *
 *	@require	RandomAccessIterator は ValueSwappable の要件を満たしている必要がある。
 *				UniformRandomNumberGenerator は uniform random number generator の要件を満たさなければならず、
 *				その戻り値の型はiterator_traits<RandomAccessIterator>::difference_type へ変換可能でなければならない。
 *
 *	@complexity	正確に (last - first) - 1 回 swap する。
 */
template <
	typename RandomAccessIterator,
	typename UniformRandomNumberGenerator,
	typename = bksge::enable_if_t<
		bksge::is_random_access_iterator<RandomAccessIterator>::value
	>
>
void
shuffle(
	RandomAccessIterator first,
	RandomAccessIterator last,
	UniformRandomNumberGenerator&& g);

}	// namespace algorithm

using algorithm::shuffle;

}	// namespace bksge

#include <bksge/fnd/algorithm/inl/shuffle_inl.hpp>

#endif // BKSGE_FND_ALGORITHM_SHUFFLE_HPP
