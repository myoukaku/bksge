/**
 *	@file	beta_impl.hpp
 *
 *	@brief	beta 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_BETA_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_BETA_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/lgamma.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
beta_unchecked(double x, double y)
{
	return std::beta(x, y);
}

inline /*BKSGE_CONSTEXPR*/ float
beta_unchecked(float x, float y)
{
	return std::betaf(x, y);
}

inline /*BKSGE_CONSTEXPR*/ long double
beta_unchecked(long double x, long double y)
{
	return std::betal(x, y);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
beta_unchecked_2(T x, T y)
{
	return bksge::exp(
		bksge::lgamma(x) + bksge::lgamma(y) - bksge::lgamma(x + y));
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
beta_unchecked(T x, T y)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(beta_unchecked_2(
		static_cast<value_type>(x), static_cast<value_type>(y)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
beta_impl(T x, T y)
{
	if (bksge::isnan(x) || bksge::isnan(y))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (x <= T(0) || y <= T(0))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	return beta_unchecked(x, y);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_BETA_IMPL_HPP
