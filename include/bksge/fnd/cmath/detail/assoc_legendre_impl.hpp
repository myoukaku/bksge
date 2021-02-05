/**
 *	@file	assoc_legendre_impl.hpp
 *
 *	@brief	assoc_legendre 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ASSOC_LEGENDRE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ASSOC_LEGENDRE_IMPL_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/double_factorial.hpp>
#include <bksge/fnd/cmath/legendre.hpp>
//#include <bksge/fnd/stdexcept/domain_error.hpp>
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
assoc_legendre_unchecked(unsigned int n, unsigned int m, double x)
{
	return std::assoc_legendre(n, m, x);
}

inline /*BKSGE_CONSTEXPR*/ float
assoc_legendre_unchecked(unsigned int n, unsigned int m, float x)
{
	return std::assoc_legendref(n, m, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
assoc_legendre_unchecked(unsigned int n, unsigned int m, long double x)
{
	return std::assoc_legendrel(n, m, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
assoc_legendre_unchecked_2(unsigned int n, unsigned int m, T x)
{
	if (m > n)
	{
		return 0;
	}

	if (m == 0)
	{
		return bksge::detail::legendre_unchecked(n, x);
	}

	// P0 = (2m-1)!!(1-x^2)^(m/2)
	T p0 = bksge::double_factorial<T>(2*m - 1) * bksge::pow(1 - x*x, T(m)/2);

	if (m == n)
	{
		return p0;
	}

	// (−1)^m  倍された値を返す
	//if ((m & 1) != 0)
	//{
	//	p0 *= -1;
	//}

	T p1 = (2 * m + 1) * x * p0;

	unsigned int c = m + 1;

	while (c < n)
	{
		bksge::swap(p0, p1);
		p1 = ((2 * c + 1) * x * p0 - (c + m) * p1) / (c + 1 - m);
		++c;
	}

	return p1;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
assoc_legendre_unchecked(unsigned int n, unsigned int m, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(assoc_legendre_unchecked_2(n, m, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
assoc_legendre_impl(unsigned int n, unsigned int m, T x)
{
	if (bksge::abs(x) > T(1))
	{
		//bksge::throw_domain_error("");
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::isnan(x))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	return assoc_legendre_unchecked(n, m, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ASSOC_LEGENDRE_IMPL_HPP
