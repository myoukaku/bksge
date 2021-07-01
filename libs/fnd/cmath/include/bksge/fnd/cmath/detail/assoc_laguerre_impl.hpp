/**
 *	@file	assoc_laguerre_impl.hpp
 *
 *	@brief	assoc_laguerre 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ASSOC_LAGUERRE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ASSOC_LAGUERRE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/stdexcept/domain_error.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
assoc_laguerre_unchecked(unsigned int n, unsigned int m, double x)
{
	return std::assoc_laguerre(n, m, x);
}

inline /*BKSGE_CONSTEXPR*/ float
assoc_laguerre_unchecked(unsigned int n, unsigned int m, float x)
{
	return std::assoc_laguerref(n, m, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
assoc_laguerre_unchecked(unsigned int n, unsigned int m, long double x)
{
	return std::assoc_laguerrel(n, m, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
assoc_laguerre_unchecked_2(unsigned int n, unsigned int m, T x)
{
	T p0 = 1;
	if (n == 0)
	{
		return p0;
	}

	T p1 = m + 1 - x;

	for (unsigned int c = 1; c < n; ++c)
	{
		bksge::swap(p0, p1);
		p1 = ((2 * c + m + 1 - x) * p0 - (c + m) * p1) / (c + 1);
	}

	return p1;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
assoc_laguerre_unchecked(unsigned int n, unsigned int m, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(assoc_laguerre_unchecked_2(n, m, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
assoc_laguerre_impl(unsigned int n, unsigned int m, T x)
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

	return assoc_laguerre_unchecked(n, m, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ASSOC_LAGUERRE_IMPL_HPP
