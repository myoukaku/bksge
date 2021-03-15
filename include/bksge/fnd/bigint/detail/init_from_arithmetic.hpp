/**
 *	@file	init_from_arithmetic.hpp
 *
 *	@brief	init_from_arithmetic 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_INIT_FROM_ARITHMETIC_HPP
#define BKSGE_FND_BIGINT_DETAIL_INIT_FROM_ARITHMETIC_HPP

#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/construct_from_float.hpp>
#include <bksge/fnd/bigint/detail/abs_to_unsigned.hpp>
#include <bksge/fnd/bigint/detail/is_zero.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

namespace init_from_arithmetic_detail
{

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR int
init_from_arithmetic_impl(VectorType& vec, Integral value, bksge::detail::overload_priority<1>)
{
	int sign = value < 0 ? -1 : 1;
	vec = bigint_algo::construct_from_integral<VectorType>(abs_to_unsigned(value));
	return sign;
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)
>
inline BKSGE_CXX14_CONSTEXPR int
init_from_arithmetic_impl(VectorType& vec, Float value, bksge::detail::overload_priority<0>)
{
	if (bksge::isnan(value) ||
		bksge::iszero(value))
	{
		vec = {0};
		return 1;
	}

	// TODO
	// inf 対応

	int sign = value < 0 ? -1 : 1;
	vec = bigint_algo::construct_from_float<VectorType>(bksge::abs(value));
	return bigint_algo::is_zero(vec) ? 1 : sign;
}

}	// namespace init_from_arithmetic_detail

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)
>
inline BKSGE_CXX14_CONSTEXPR int
init_from_arithmetic(VectorType& vec, Arithmetic value)
{
	return init_from_arithmetic_detail::init_from_arithmetic_impl(
		vec, value, bksge::detail::overload_priority<1>{});
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_INIT_FROM_ARITHMETIC_HPP
