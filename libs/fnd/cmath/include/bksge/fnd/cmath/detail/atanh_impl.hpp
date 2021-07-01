/**
 *	@file	atanh_impl.hpp
 *
 *	@brief	atanh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ATANH_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ATANH_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
atanh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_atanhf(x);
}

inline BKSGE_CONSTEXPR double
atanh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_atanh(x);
}

inline BKSGE_CONSTEXPR long double
atanh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_atanhl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
atanh_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::atanh(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
atanh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::iszero(x) ?
			x :
		x == FloatType(1) ?
			std::numeric_limits<FloatType>::infinity() :
		x == FloatType(-1) ?
			-std::numeric_limits<FloatType>::infinity() :
		bksge::fabs(x) > FloatType(1) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		atanh_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ATANH_IMPL_HPP
