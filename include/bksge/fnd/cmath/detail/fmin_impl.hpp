/**
 *	@file	fmin_impl.hpp
 *
 *	@brief	fmin 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FMIN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FMIN_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
fmin_unchecked(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_fminf(x, y);
}

inline BKSGE_CONSTEXPR double
fmin_unchecked(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_fmin(x, y);
}

inline BKSGE_CONSTEXPR long double
fmin_unchecked(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_fminl(x, y);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
fmin_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return x < y ? x : y;
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fmin_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			y :
		bksge::isnan(y) ?
			x :
		fmin_unchecked(x, y);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FMIN_IMPL_HPP
