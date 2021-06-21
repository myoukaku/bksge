/**
 *	@file	fdim_impl.hpp
 *
 *	@brief	fdim 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FDIM_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FDIM_IMPL_HPP

#include <bksge/fnd/cmath/fdim.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
fdim_unchecked(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_fdimf(x, y);
}

inline BKSGE_CONSTEXPR double
fdim_unchecked(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_fdim(x, y);
}

inline BKSGE_CONSTEXPR long double
fdim_unchecked(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_fdiml(x, y);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
fdim_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return x > y ? x - y : T(0);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fdim_impl_2(FloatType x, FloatType y, FloatType inf) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(y) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x == inf ?
			y == inf ?
				FloatType(0) :
			inf :
		x == -inf ?
			FloatType(0) :
		y == inf ?
			FloatType(0) :
		y == -inf ?
			inf :
		fdim_unchecked(x, y);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fdim_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return fdim_impl_2(x, y, std::numeric_limits<FloatType>::infinity());
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FDIM_IMPL_HPP
