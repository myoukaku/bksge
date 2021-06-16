/**
 *	@file	construct_from_iterator.hpp
 *
 *	@brief	construct_from_iterator 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_ITERATOR_HPP
#define BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_ITERATOR_HPP

#include <bksge/fnd/bigint/detail/construct_from_size.hpp>
#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType, typename Iterator>
inline BKSGE_CXX14_CONSTEXPR VectorType
construct_from_iterator(Iterator first, Iterator last)
{
	namespace ranges = bksge::ranges;
	auto const N = ranges::distance(first, last);
	auto result = bigint_algo::construct_from_size<VectorType>(N);
	ranges::copy(first, last, ranges::begin(result));
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_ITERATOR_HPP
