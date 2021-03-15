/**
 *	@file	construct_from_vector.hpp
 *
 *	@brief	construct_from_vector 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_VECTOR_HPP
#define BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_VECTOR_HPP

#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/construct_from_size.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/algorithm/ranges/copy.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename ResultType, typename VectorType>
inline BKSGE_CXX14_CONSTEXPR ResultType
construct_from_vector(VectorType const& vec)
{
	namespace ranges = bksge::ranges;
	auto const NA = bigint_algo::get_digits(vec);
	auto result = bigint_algo::construct_from_size<ResultType>(NA);
	auto const NB = ranges::size(result);
	ranges::copy(
		ranges::begin(vec), ranges::begin(vec) + bksge::min(NA, NB),
		ranges::begin(result));
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_VECTOR_HPP
