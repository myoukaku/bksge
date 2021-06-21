/**
 *	@file	ellint_1_impl.hpp
 *
 *	@brief	ellint_1 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ELLINT_1_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ELLINT_1_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/comp_ellint_1.hpp>
#include <bksge/fnd/cmath/detail/ellint_rf.hpp>
//#include <bksge/fnd/cmath/detail/ellint_rj.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(__cpp_lib_math_special_functions) && (__cpp_lib_math_special_functions >= 201603)

inline /*BKSGE_CONSTEXPR*/ double
ellint_1_unchecked(double k, double phi_)
{
	return std::ellint_1(k, phi_);
}

inline /*BKSGE_CONSTEXPR*/ float
ellint_1_unchecked(float k, float phi_)
{
	return std::ellint_1f(k, phi_);
}

inline /*BKSGE_CONSTEXPR*/ long double
ellint_1_unchecked(long double k, long double phi_)
{
	return std::ellint_1l(k, phi_);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_1_unchecked_2(T k, T phi_)
{
	//  Reduce phi_ to -pi/2 < phi_ < +pi/2.
	const int n = static_cast<int>(bksge::floor(phi_ / bksge::pi_t<T>() + T(0.5)));
	const T phi_red = phi_ - n * bksge::pi_t<T>();

	const T s = bksge::sin(phi_red);
	const T c = bksge::cos(phi_red);

	const T F = s * bksge::detail::ellint_rf(c * c, T(1) - k * k * s * s, T(1));

	if (n == 0)
	{
		return F;
	}
	else
	{
		return F + T(2) * n * bksge::comp_ellint_1(k);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_1_unchecked(T k, T phi_)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(ellint_1_unchecked_2(
		static_cast<value_type>(k), static_cast<value_type>(phi_)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_1_impl(T k, T phi_)
{
	if (bksge::isnan(k) || bksge::isnan(phi_))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) > T(1))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) == T(1) && bksge::abs(phi_) >= (bksge::pi_t<T>() / 2))
	{
		return std::numeric_limits<T>::infinity();
	}

	return ellint_1_unchecked(k, phi_);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ELLINT_1_IMPL_HPP
