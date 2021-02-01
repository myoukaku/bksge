/**
 *	@file	hypot_impl.hpp
 *
 *	@brief	hypot 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_HYPOT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_HYPOT_IMPL_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
hypot_unchecked(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_hypotf(x, y);
}

inline BKSGE_CONSTEXPR double
hypot_unchecked(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_hypot(x, y);
}

inline BKSGE_CONSTEXPR long double
hypot_unchecked(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_hypotl(x, y);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
hypot_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return std::hypot(x, y);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
hypot_unchecked(T x, T y, T z) BKSGE_NOEXCEPT
{
#if defined(__cpp_lib_hypot) && (__cpp_lib_hypot >= 201603)
	return std::hypot(x, y, z);
#else
	T const a = bksge::max({bksge::abs(x), bksge::abs(y), bksge::abs(z)});
	if (a != 0)
	{
		T const xx = x / a;
		T const yy = y / a;
		T const zz = z / a;
		return a * bksge::sqrt(xx*xx + yy*yy + zz*zz);
	}
	else
	{
		return {};
	}
#endif
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
hypot_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			bksge::fabs(y) :
		bksge::iszero(y) ?
			bksge::fabs(x) :
		bksge::isinf(x) || bksge::isinf(y) ?
			bksge::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) || bksge::isnan(y) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		hypot_unchecked(x, y);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
hypot_impl(FloatType x, FloatType y, FloatType z) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) && bksge::iszero(y) ?
			bksge::fabs(z) :
		bksge::iszero(y) && bksge::iszero(z) ?
			bksge::fabs(x) :
		bksge::iszero(z) && bksge::iszero(x) ?
			bksge::fabs(y) :
		bksge::isinf(x) || bksge::isinf(y) || bksge::isinf(z) ?
			bksge::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) || bksge::isnan(y) || bksge::isnan(z) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		hypot_unchecked(x, y, z);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_HYPOT_IMPL_HPP
