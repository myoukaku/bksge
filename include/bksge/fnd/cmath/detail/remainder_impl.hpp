/**
 *	@file	remainder_impl.hpp
 *
 *	@brief	remainder 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_REMAINDER_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_REMAINDER_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/round_half_even.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
//#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
remainder_unchecked(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_remainderf(x, y);
}

inline BKSGE_CONSTEXPR double
remainder_unchecked(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_remainder(x, y);
}

inline BKSGE_CONSTEXPR long double
remainder_unchecked(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_remainderl(x, y);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
remainder_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return x - (bksge::round_half_even(x / y) * y);
//	return std::remainder(x, y);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
remainder_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ||
		bksge::isnan(y) ||
		bksge::isinf(x) ||
		bksge::iszero(y) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		remainder_unchecked(x, y);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_REMAINDER_IMPL_HPP
