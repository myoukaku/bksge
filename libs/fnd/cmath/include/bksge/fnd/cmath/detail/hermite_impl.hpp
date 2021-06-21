/**
 *	@file	hermite_impl.hpp
 *
 *	@brief	hermite 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_HERMITE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_HERMITE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
hermite_unchecked(unsigned int n, double x)
{
	return std::hermite(n, x);
}

inline /*BKSGE_CONSTEXPR*/ float
hermite_unchecked(unsigned int n, float x)
{
	return std::hermitef(n, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
hermite_unchecked(unsigned int n, long double x)
{
	return std::hermitel(n, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
hermite_unchecked_2(unsigned int n, T x)
{
	//  Compute H_0.
	T H_0 = 1;
	if (n == 0)
	{
		return H_0;
	}

	//  Compute H_1.
	T H_1 = 2 * x;
	if (n == 1)
	{
		return H_1;
	}

	//  Compute H_n.
	T H_n = 0;
	T H_nm1 = H_1;
	T H_nm2 = H_0;
	for (unsigned int i = 2; i <= n; ++i)
	{
		H_n = 2 * (x * H_nm1 - (i - 1) * H_nm2);
		H_nm2 = H_nm1;
		H_nm1 = H_n;
	}

	return H_n;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
hermite_unchecked(unsigned int n, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(hermite_unchecked_2(n, static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
hermite_impl(unsigned int n, T x)
{
	if (bksge::isnan(x))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	return hermite_unchecked(n, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_HERMITE_IMPL_HPP
