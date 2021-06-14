/**
 *	@file	legendre_impl.hpp
 *
 *	@brief	legendre 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LEGENDRE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LEGENDRE_IMPL_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
legendre_unchecked(unsigned int n, double x)
{
	return std::legendre(n, x);
}

inline /*BKSGE_CONSTEXPR*/ float
legendre_unchecked(unsigned int n, float x)
{
	return std::legendref(n, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
legendre_unchecked(unsigned int n, long double x)
{
	return std::legendrel(n, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
legendre_unchecked_2(unsigned int n, T x)
{
	T p0 = 1;
	if (n == 0)
	{
		return p0;
	}

	T p1 = x;
	unsigned c = 1;
	while (c < n)
	{
		bksge::swap(p0, p1);
		p1 = ((2 * c + 1) * x * p0 - c * p1) / (c + 1);
		++c;
	}
	return p1;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
legendre_unchecked(unsigned int n, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(legendre_unchecked_2(n, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
legendre_impl(unsigned int n, T x)
{
	if (bksge::abs(x) > T(1))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::isnan(x))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	return legendre_unchecked(n, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LEGENDRE_IMPL_HPP
