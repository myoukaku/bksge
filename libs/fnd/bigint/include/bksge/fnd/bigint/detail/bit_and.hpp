/**
 *	@file	bit_and.hpp
 *
 *	@brief	bit_and 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIT_AND_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIT_AND_HPP

#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/resize.hpp>
#include <bksge/fnd/bigint/detail/remove_leading_zeros.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR void
bit_and(VectorType& lhs, VectorType const& rhs)
{
	auto const NA = bigint_algo::get_digits(lhs);
	auto const NB = bigint_algo::get_digits(rhs);

	bigint_algo::resize(lhs, bksge::max(NA, NB));
	auto const N = bksge::ranges::size(lhs);

	std::size_t i = 0;
	for (; i < NB; ++i)
	{
		lhs[i] &= rhs[i];
	}
	for (; i < N; ++i)
	{
		lhs[i] &= 0;
	}

	bigint_algo::remove_leading_zeros(lhs);
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIT_AND_HPP
