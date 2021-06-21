/**
 *	@file	acos_impl.hpp
 *
 *	@brief	acos 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ACOS_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ACOS_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
acos_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_acosf(x);
}

inline BKSGE_CONSTEXPR double
acos_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_acos(x);
}

inline BKSGE_CONSTEXPR long double
acos_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_acosl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
acos_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::acos(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
acos_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			x :
		bksge::fabs(x) > FloatType(1) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x == FloatType(1) ?
			FloatType(0) :
		acos_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ACOS_IMPL_HPP
