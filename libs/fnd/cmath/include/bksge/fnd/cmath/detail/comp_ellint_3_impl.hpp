/**
 *	@file	comp_ellint_3_impl.hpp
 *
 *	@brief	comp_ellint_3 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_3_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_3_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/detail/ellint_rf.hpp>
#include <bksge/fnd/cmath/detail/ellint_rj.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
comp_ellint_3_unchecked(double k, double nu)
{
	return std::comp_ellint_3(k, nu);
}

inline /*BKSGE_CONSTEXPR*/ float
comp_ellint_3_unchecked(float k, float nu)
{
	return std::comp_ellint_3f(k, nu);
}

inline /*BKSGE_CONSTEXPR*/ long double
comp_ellint_3_unchecked(long double k, long double nu)
{
	return std::comp_ellint_3l(k, nu);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_3_unchecked_2(T k, T nu)
{
	T const x = T(0);
	T const y = T(1) - k * k;
	T const z = T(1);
	return bksge::detail::ellint_rf(x, y, z) +
		nu * bksge::detail::ellint_rj(x, y, z, T(1) - nu) / T(3);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_3_unchecked(T k, T nu)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(comp_ellint_3_unchecked_2(
		static_cast<value_type>(k), static_cast<value_type>(nu)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
comp_ellint_3_impl(T k, T nu)
{
	if (bksge::isnan(k) || bksge::isnan(nu))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) > T(1))
	{
		return bksge::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) == T(1))
	{
		return bksge::numeric_limits<T>::infinity();
	}

	return comp_ellint_3_unchecked(k, nu);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_COMP_ELLINT_3_IMPL_HPP
