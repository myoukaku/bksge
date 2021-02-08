/**
 *	@file	cyl_neumann_impl.hpp
 *
 *	@brief	cyl_neumann 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CYL_NEUMANN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_CYL_NEUMANN_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
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
cyl_neumann_unchecked(double nu, double x)
{
	return std::cyl_neumann(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ float
cyl_neumann_unchecked(float nu, float x)
{
	return std::cyl_neumannf(nu, x);
}

inline /*BKSGE_CONSTEXPR*/ long double
cyl_neumann_unchecked(long double nu, long double x)
{
	return std::cyl_neumannl(nu, x);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_neumann_unchecked_2(T nu, T x)
{
	if (x > T(1000))
	{
		T J_nu, N_nu;
		bksge::detail::cyl_bessel_jn_asymp(nu, x, J_nu, N_nu);
		return N_nu;
	}
	else
	{
		T J_nu, N_nu, Jp_nu, Np_nu;
		bksge::detail::bessel_jn(nu, x, J_nu, N_nu, Jp_nu, Np_nu);
		return N_nu;
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_neumann_unchecked(T nu, T x)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(cyl_neumann_unchecked_2(
		static_cast<value_type>(nu), static_cast<value_type>(x)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_neumann_impl(T nu, T x)
{
	if (bksge::isnan(nu) || bksge::isnan(x))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	return cyl_neumann_unchecked(nu, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CYL_NEUMANN_IMPL_HPP
