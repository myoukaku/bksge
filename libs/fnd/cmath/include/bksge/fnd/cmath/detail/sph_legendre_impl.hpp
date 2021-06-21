/**
 *	@file	sph_legendre_impl.hpp
 *
 *	@brief	sph_legendre 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SPH_LEGENDRE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SPH_LEGENDRE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/log1p.hpp>
#include <bksge/fnd/cmath/lgamma.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/legendre.hpp>
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
sph_legendre_unchecked(unsigned int l, unsigned int m, double theta)
{
	return std::sph_legendre(l, m, theta);
}

inline /*BKSGE_CONSTEXPR*/ float
sph_legendre_unchecked(unsigned int l, unsigned int m, float theta)
{
	return std::sph_legendref(l, m, theta);
}

inline /*BKSGE_CONSTEXPR*/ long double
sph_legendre_unchecked(unsigned int l, unsigned int m, long double theta)
{
	return std::sph_legendrel(l, m, theta);
}

#else

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_legendre_unchecked_2(unsigned int l, unsigned int m, T theta)
{
	const T x = bksge::cos(theta);

	if (m > l)
	{
		return T(0);
	}
	else if (m == 0)
	{
		T p = bksge::detail::legendre_unchecked(l, x);
		T fact = bksge::sqrt(T(2 * l + 1) / (T(4) * bksge::pi_t<T>()));
		p *= fact;
		return p;
	}
	else if (x == T(1) || x == -T(1))
	{
		//  m > 0 here
		return T(0);
	}
	else
	{
		// m > 0 and |x| < 1 here

		// Starting value for recursion.
		// Y_m^m(x) = sqrt( (2m+1)/(4pi m) gamma(m+1/2)/gamma(m) )
		//             (-1)^m (1-x^2)^(m/2) / pi^(1/4)
		const T sgn = (m % 2 == 1 ? -T(1) : T(1));
		const T y_mp1m_factor = x * bksge::sqrt(T(2 * m + 3));
		const T lncirc = bksge::log1p(-x * x);

		//  Gamma(m+1/2) / Gamma(m)
		const T lnpoch = bksge::lgamma(T(m + T(0.5L))) - bksge::lgamma(T(m));
		const T lnpre_val =
			-T(0.25L) * bksge::log(bksge::pi_t<T>())
			+ T(0.5L) * (lnpoch + m * lncirc);
		const T sr = bksge::sqrt((T(2) + T(1) / m) / (T(4) * bksge::pi_t<T>()));
		T y_mm = sgn * sr * bksge::exp(lnpre_val);
		T y_mp1m = y_mp1m_factor * y_mm;

		if (l == m)
		{
			return y_mm;
		}
		else if (l == m + 1)
		{
			return y_mp1m;
		}
		else
		{
			T y_lm = T(0);

			// Compute Y_l^m, l > m+1, upward recursion on l.
			for (unsigned int ll = m + 2; ll <= l; ++ll)
			{
				const T rat1 = T(ll - m) / T(ll + m);
				const T rat2 = T(ll - m - 1) / T(ll + m - 1);
				const T fact1 = bksge::sqrt(rat1 * T(2 * ll + 1) * T(2 * ll - 1));
				const T fact2 = bksge::sqrt(rat1 * rat2 * T(2 * ll + 1) / T(2 * ll - 3));
				y_lm = (x * y_mp1m * fact1 - (ll + m - 1) * y_mm * fact2) / T(ll - m);
				y_mm = y_mp1m;
				y_mp1m = y_lm;
			}

			return y_lm;
		}
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_legendre_unchecked(unsigned int l, unsigned int m, T theta)
{
	using value_type = bksge::float_promote_t<double, T>;
	return static_cast<T>(sph_legendre_unchecked_2(l, m, static_cast<value_type>(theta)));
}

#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
sph_legendre_impl(unsigned int l, unsigned int m, T theta)
{
	if (bksge::isnan(theta))
	{
		return std::numeric_limits<T>::quiet_NaN();
	}

	return sph_legendre_unchecked(l, m, theta);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SPH_LEGENDRE_IMPL_HPP
