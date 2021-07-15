/**
 *	@file	multiply.hpp
 *
 *	@brief	multiply 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MULTIPLY_HPP
#define BKSGE_FND_BIGINT_DETAIL_MULTIPLY_HPP

#include <bksge/fnd/bigint/detail/multiply_naive.hpp>
#include <bksge/fnd/bigint/detail/multiply_ntt.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::vector<T>
multiply(bksge::vector<T> const& lhs, bksge::vector<T> const& rhs)
{
	return multiply_naive(lhs, rhs);
//	return multiply_ntt(lhs, rhs);
}

template <typename T, std::size_t N>
inline BKSGE_CXX14_CONSTEXPR bksge::array<T, N>
multiply(bksge::array<T, N> const& lhs, bksge::array<T, N> const& rhs)
{
	return multiply_naive(lhs, rhs);
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR VectorType
multiply(VectorType const& lhs, Integral rhs)
{
	return multiply(lhs, bigint_algo::construct_from_integral<VectorType>(rhs));
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MULTIPLY_HPP
