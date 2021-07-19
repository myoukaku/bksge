﻿/**
 *	@file	laguerre_impl.hpp
 *
 *	@brief	laguerre 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LAGUERRE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LAGUERRE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/stdexcept/domain_error.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>
#include <utility>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
laguerre_unchecked(unsigned int n, double x)
{
	return std::laguerre(n, x);
}

inline /*BKSGE_CONSTEXPR*/ float
laguerre_unchecked(unsigned int n, float x)
{
	return std::laguerref(n, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
laguerre_unchecked(unsigned int n, long double x)
{
	return std::laguerrel(n, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
laguerre_unchecked_2(unsigned int n, T x)
{
	T p0 = 1;
	if (n == 0)
	{
		return p0;
	}

	T p1 = 1 - x;

	for (unsigned int c = 1; c < n; ++c)
	{
		using std::swap;
		swap(p0, p1);
		p1 = ((((2 * c) + 1 - x) * p0) - (c * p1)) / (c + 1);
	}

	return p1;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
laguerre_unchecked(unsigned int n, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(laguerre_unchecked_2(n, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
laguerre_impl(unsigned int n, T x)
{
	if (bksge::isnan(x))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (x < T(0))
	{
		//bksge::throw_domain_error("Negative argument in poly_laguerre.");
		return std::numeric_limits<T>::quiet_NaN();
	}

	return laguerre_unchecked(n, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LAGUERRE_IMPL_HPP
