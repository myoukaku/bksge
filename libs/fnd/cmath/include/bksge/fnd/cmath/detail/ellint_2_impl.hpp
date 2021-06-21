/**
 *	@file	ellint_2_impl.hpp
 *
 *	@brief	ellint_2 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ELLINT_2_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ELLINT_2_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/comp_ellint_2.hpp>
#include <bksge/fnd/cmath/detail/ellint_rf.hpp>
#include <bksge/fnd/cmath/detail/ellint_rd.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
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
ellint_2_unchecked(double k, double phi_)
{
	return std::ellint_2(k, phi_);
}

inline /*BKSGE_CONSTEXPR*/ float
ellint_2_unchecked(float k, float phi_)
{
	return std::ellint_2f(k, phi_);
}

inline /*BKSGE_CONSTEXPR*/ long double
ellint_2_unchecked(long double k, long double phi_)
{
	return std::ellint_2l(k, phi_);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_2_unchecked_2(T k, T phi_)
{
	//  Reduce phi to -pi/2 < phi < +pi/2.
	int const n = static_cast<int>(bksge::floor(phi_ / bksge::pi_t<T>() + T(0.5)));
	T const phi_red = phi_ - n * bksge::pi_t<T>();

	T const kk = k * k;
	T const s = bksge::sin(phi_red);
	T const ss = s * s;
	T const sss = ss * s;
	T const c = bksge::cos(phi_red);
	T const cc = c * c;

	T const E = s * bksge::detail::ellint_rf(cc, T(1) - kk * ss, T(1)) -
		kk * sss * bksge::detail::ellint_rd(cc, T(1) - kk * ss, T(1)) / T(3);

	if (n == 0)
	{
		return E;
	}
	else
	{
		return E + T(2) * n * bksge::comp_ellint_2(k);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_2_unchecked(T k, T phi_)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(ellint_2_unchecked_2(
		static_cast<value_type>(k), static_cast<value_type>(phi_)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_2_impl(T k, T phi_)
{
	if (bksge::isnan(k) || bksge::isnan(phi_))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	if (bksge::abs(k) > T(1))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	//if (bksge::abs(k) == T(1) && bksge::abs(phi_) >= (bksge::pi_t<T>() / 2))
	//{
	//	return std::numeric_limits<T>::infinity();
	//}

	return ellint_2_unchecked(k, phi_);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ELLINT_2_IMPL_HPP
