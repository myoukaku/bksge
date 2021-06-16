/**
 *	@file	pow_impl.hpp
 *
 *	@brief	pow 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_POW_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_POW_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/is_odd.hpp>
#include <bksge/fnd/cmath/is_integer.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
pow_unchecked(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_powf(x, y);
}

inline BKSGE_CONSTEXPR double
pow_unchecked(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_pow(x, y);
}

inline BKSGE_CONSTEXPR long double
pow_unchecked(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_powl(x, y);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
pow_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return std::pow(x, y);	// TODO
}

#endif

template <typename T>
inline BKSGE_CONSTEXPR T
pow_impl_2(T x, T y, T inf, T nan) BKSGE_NOEXCEPT
{
	//pow(+0, exp), where exp is a negative odd integer, returns +∞ and raises FE_DIVBYZERO
	//pow(-0, exp), where exp is a negative odd integer, returns -∞ and raises FE_DIVBYZERO
	//pow(±0, exp), where exp is negative, finite, and is an even integer or a non-integer, returns +∞ and raises FE_DIVBYZERO
	//pow(±0, -∞) returns +∞ and may raise FE_DIVBYZERO
	//pow(+0, exp), where exp is a positive odd integer, returns +0
	//pow(-0, exp), where exp is a positive odd integer, returns -0
	//pow(±0, exp), where exp is positive non-integer or a positive even integer, returns +0
	//pow(-1, ±∞) returns 1
	//pow(+1, exp) returns 1 for any exp, even when exp is NaN
	//pow(base, ±0) returns 1 for any base, even when base is NaN
	//pow(base, exp) returns NaN and raises FE_INVALID if base is finite and negative and exp is finite and non-integer.
	//pow(base, -∞) returns +∞ for any |base|<1
	//pow(base, -∞) returns +0 for any |base|>1
	//pow(base, +∞) returns +0 for any |base|<1
	//pow(base, +∞) returns +∞ for any |base|>1
	//pow(-∞, exp) returns -0 if exp is a negative odd integer
	//pow(-∞, exp) returns +0 if exp is a negative non-integer or even integer
	//pow(-∞, exp) returns -∞ if exp is a positive odd integer
	//pow(-∞, exp) returns +∞ if exp is a positive non-integer or even integer
	//pow(+∞, exp) returns +0 for any negative exp
	//pow(+∞, exp) returns +∞ for any positive exp
	//except where specified above, if any argument is NaN, NaN is returned

	return
		bksge::iszero(x) ?
			bksge::signbit(y) ?
				bksge::is_odd(y) ?
					bksge::copysign(inf, x) :
				inf :
			bksge::is_odd(y) ?
				x :
			T(0) :
		x == T(-1) && bksge::isinf(y) ?
			T(1) :
		x == T(1) ?
			T(1) :
		bksge::iszero(y) ?
			T(1) :
		bksge::isfinite(x) && bksge::signbit(x) && bksge::isfinite(y) && !bksge::is_integer(y) ?
			nan :
		bksge::isinf(y) ?
			bksge::signbit(y) ?
				bksge::fabs(x) < T(1) ?
					inf :
				T(0) :
			bksge::fabs(x) < T(1) ?
				T(0) :
			inf :
		bksge::isinf(x) ?
			bksge::signbit(x) ?
				bksge::signbit(y) ?
					bksge::is_odd(y) ?
						-T(0) :
					T(0) :
				bksge::is_odd(y) ?
					-inf :
				inf :
			bksge::signbit(y) ?
				T(0) :
			inf :
		bksge::isnan(x) || bksge::isnan(y) ?
			nan :
		pow_unchecked(x, y);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
pow_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return pow_impl_2(x, y,
		bksge::numeric_limits<FloatType>::infinity(),
		bksge::numeric_limits<FloatType>::quiet_NaN());
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_POW_IMPL_HPP
