/**
 *	@file	cyl_bessel_k_impl.hpp
 *
 *	@brief	cyl_bessel_k 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_K_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_K_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/detail/bessel_ik.hpp>
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
cyl_bessel_k_unchecked(double nu, double x)
{
	return std::cyl_bessel_k(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ float
cyl_bessel_k_unchecked(float nu, float x)
{
	return std::cyl_bessel_kf(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
cyl_bessel_k_unchecked(long double nu, long double x)
{
	return std::cyl_bessel_kl(nu, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_k_unchecked_2(T nu, T x)
{
	T I_nu, K_nu, Ip_nu, Kp_nu;
	bksge::detail::bessel_ik(nu, x, I_nu, K_nu, Ip_nu, Kp_nu);
	return K_nu;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_k_unchecked(T nu, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(cyl_bessel_k_unchecked_2(
		static_cast<value_type>(nu), static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_k_impl(T nu, T x)
{
	if (bksge::isnan(nu) || bksge::isnan(x))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	return cyl_bessel_k_unchecked(nu, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_K_IMPL_HPP
