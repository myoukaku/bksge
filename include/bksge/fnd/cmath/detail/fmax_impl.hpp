/**
 *	@file	fmax_impl.hpp
 *
 *	@brief	fmax 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FMAX_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FMAX_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
fmax_unchecked(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_fmaxf(x, y);
}

inline BKSGE_CONSTEXPR double
fmax_unchecked(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_fmax(x, y);
}

inline BKSGE_CONSTEXPR long double
fmax_unchecked(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_fmaxl(x, y);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
fmax_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return x < y ? y : x;
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fmax_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			y :
		bksge::isnan(y) ?
			x :
		fmax_unchecked(x, y);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FMAX_IMPL_HPP
