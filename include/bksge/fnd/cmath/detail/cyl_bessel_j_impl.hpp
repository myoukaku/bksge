/**
 *	@file	cyl_bessel_j_impl.hpp
 *
 *	@brief	cyl_bessel_j 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_J_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_J_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/detail/cyl_bessel_ij_series.hpp>
#include <bksge/fnd/cmath/detail/cyl_bessel_jn_asymp.hpp>
#include <bksge/fnd/cmath/detail/bessel_jn.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
cyl_bessel_j_unchecked(double nu, double x)
{
	return std::cyl_bessel_j(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ float
cyl_bessel_j_unchecked(float nu, float x)
{
	return std::cyl_bessel_jf(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
cyl_bessel_j_unchecked(long double nu, long double x)
{
	return std::cyl_bessel_jl(nu, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_j_unchecked_2(T nu, T x)
{
	if (x * x < T(10) * (nu + T(1)))
	{
		return bksge::detail::cyl_bessel_ij_series(nu, x, -T(1), 200);
	}
	else if (x > T(1000))
	{
		T J_nu, N_nu;
		bksge::detail::cyl_bessel_jn_asymp(nu, x, J_nu, N_nu);
		return J_nu;
	}
	else
	{
		T J_nu, N_nu, Jp_nu, Np_nu;
		bksge::detail::bessel_jn(nu, x, J_nu, N_nu, Jp_nu, Np_nu);
		return J_nu;
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_j_unchecked(T nu, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(cyl_bessel_j_unchecked_2(
		static_cast<value_type>(nu), static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_j_impl(T nu, T x)
{
	if (bksge::isnan(nu) || bksge::isnan(x))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	return cyl_bessel_j_unchecked(nu, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_J_IMPL_HPP
