/**
 *	@file	cyl_bessel_i_impl.hpp
 *
 *	@brief	cyl_bessel_i 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_I_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_I_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/detail/cyl_bessel_ij_series.hpp>
#include <bksge/fnd/cmath/detail/bessel_ik.hpp>
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
cyl_bessel_i_unchecked(double nu, double x)
{
	return std::cyl_bessel_i(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ float
cyl_bessel_i_unchecked(float nu, float x)
{
	return std::cyl_bessel_if(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
cyl_bessel_i_unchecked(long double nu, long double x)
{
	return std::cyl_bessel_il(nu, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_i_unchecked_2(T nu, T x)
{
	if (x * x < T(10) * (nu + T(1)))
	{
		return bksge::detail::cyl_bessel_ij_series(nu, x, +T(1), 200);
	}
	else
	{
		T i_nu, k_nu, ip_nu, kp_nu;
		bksge::detail::bessel_ik(nu, x, i_nu, k_nu, ip_nu, kp_nu);
		return i_nu;
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_i_unchecked(T nu, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(cyl_bessel_i_unchecked_2(
		static_cast<value_type>(nu), static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_i_impl(T nu, T x)
{
	if (bksge::isnan(nu) || bksge::isnan(x))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	return cyl_bessel_i_unchecked(nu, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_I_IMPL_HPP
