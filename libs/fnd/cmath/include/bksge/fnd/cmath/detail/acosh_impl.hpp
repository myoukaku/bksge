/**
 *	@file	acosh_impl.hpp
 *
 *	@brief	acosh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ACOSH_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ACOSH_IMPL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
acosh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_acoshf(x);
}

inline BKSGE_CONSTEXPR double
acosh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_acosh(x);
}

inline BKSGE_CONSTEXPR long double
acosh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_acoshl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
acosh_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::acosh(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
acosh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			x :
		x < FloatType(1) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x == FloatType(1) ?
			FloatType(0) :
		bksge::isinf(x) ?
			x :
		acosh_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ACOSH_IMPL_HPP
