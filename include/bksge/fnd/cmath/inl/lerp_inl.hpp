/**
 *	@file	lerp_inl.hpp
 *
 *	@brief	lerp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_LERP_INL_HPP
#define BKSGE_FND_CMATH_INL_LERP_INL_HPP

#include <bksge/fnd/cmath/lerp.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
lerp_impl(T a, T b, T t) BKSGE_NOEXCEPT
{
	if ((a <= 0 && b >= 0) || (a >= 0 && b <= 0))
	{
		return t * b + (1 - t) * a;
	}

	if (t == 1)
	{
		return b;		// exact
	}

	// Exact at t=0, monotonic except near t=1,
	// bounded, determinate, and consistent:
	const T x = a + t * (b - a);
	return (t > 1) == (b > a) ?
		(b < x ? x : b) :
		(b > x ? x : b);  // monotonic near t=1
}

}	// namespace detail

inline BKSGE_CXX14_CONSTEXPR float
lerp(float a, float b, float t) BKSGE_NOEXCEPT
{
	return detail::lerp_impl(a, b, t);
}

inline BKSGE_CXX14_CONSTEXPR double
lerp(double a, double b, double t) BKSGE_NOEXCEPT
{
	return detail::lerp_impl(a, b, t);
}

inline BKSGE_CXX14_CONSTEXPR long double
lerp(long double a, long double b, long double t) BKSGE_NOEXCEPT
{
	return detail::lerp_impl(a, b, t);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_LERP_INL_HPP
