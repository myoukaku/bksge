/**
 *	@file	cyl_bessel_jn_asymp.hpp
 *
 *	@brief	cyl_bessel_jn_asymp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_JN_ASYMP_HPP
#define BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_JN_ASYMP_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
cyl_bessel_jn_asymp(T nu, T x, T& Jnu, T& Nnu)
{
	const T mu = T(4) * nu * nu;
	const T x8 = T(8) * x;

	T P = T(0);
	T Q = T(0);

	T k = T(0);
	T term = T(1);

	int epsP = 0;
	int epsQ = 0;

	T eps = bksge::numeric_limits<T>::epsilon();

	do
	{
		term *= (k == 0
			? T(1)
			: -(mu - (2 * k - 1) * (2 * k - 1)) / (k * x8));

		epsP = bksge::abs(term) < eps * bksge::abs(P);
		P += term;

		k++;

		term *= (mu - (2 * k - 1) * (2 * k - 1)) / (k * x8);
		epsQ = bksge::abs(term) < eps * bksge::abs(Q);
		Q += term;

		if (epsP && epsQ && k > (nu / 2.))
		{
			break;
		}

		k++;
	}
	while (k < 1000);

	const T chi = x - (nu + T(0.5L)) * (bksge::pi_t<T>() / 2);

	const T c = bksge::cos(chi);
	const T s = bksge::sin(chi);

	const T coef = bksge::sqrt(T(2) / (bksge::pi_t<T>() * x));

	Jnu = coef * (c * P - s * Q);
	Nnu = coef * (s * P + c * Q);

	return;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_JN_ASYMP_HPP
