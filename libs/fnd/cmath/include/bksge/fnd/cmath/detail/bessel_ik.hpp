/**
 *	@file	bessel_ik.hpp
 *
 *	@brief	bessel_ik 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_BESSEL_IK_HPP
#define BKSGE_FND_CMATH_DETAIL_BESSEL_IK_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/sinh.hpp>
#include <bksge/fnd/cmath/cosh.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/detail/gamma_temme.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4456);	// '...' hides previous local declaration
BKSGE_WARNING_DISABLE_MSVC(4459);	// declaration of 'e' hides global declaration

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
bessel_ik(T nu, T x, T& Inu, T& Knu, T& Ipnu, T& Kpnu)
{
	if (x == T(0))
	{
		if (nu == T(0))
		{
			Inu = T(1);
			Ipnu = T(0);
		}
		else if (nu == T(1))
		{
			Inu = T(0);
			Ipnu = T(0.5L);
		}
		else
		{
			Inu = T(0);
			Ipnu = T(0);
		}
		Knu = std::numeric_limits<T>::infinity();
		Kpnu = -std::numeric_limits<T>::infinity();
		return;
	}

	const T eps = std::numeric_limits<T>::epsilon();
	const T fp_min = T(10) * std::numeric_limits<T>::epsilon();
	const int max_iter = 15000;
	const T x_min = T(2);

	const int nl = static_cast<int>(nu + T(0.5L));

	const T mu = nu - nl;
	const T mu2 = mu * mu;
	const T xi = T(1) / x;
	const T xi2 = T(2) * xi;
	T h = nu * xi;
	if (h < fp_min)
	{
		h = fp_min;
	}
	T b = xi2 * nu;
	T d = T(0);
	T c = h;
	int i = 1;
	for (; i <= max_iter; ++i)
	{
		b += xi2;
		d = T(1) / (b + d);
		c = b + T(1) / c;
		const T del = c * d;
		h *= del;
		if (bksge::abs(del - T(1)) < eps)
		{
			break;
		}
	}

	if (i > max_iter)
	{
		bksge::throw_runtime_error(
			"Argument x too large in bessel_ik; "
			"try asymptotic expansion.");
	}

	T Inul = fp_min;
	T Ipnul = h * Inul;
	T Inul1 = Inul;
	T Ipnu1 = Ipnul;
	T fact = nu * xi;
	for (int l = nl; l >= 1; --l)
	{
		const T Inutemp = fact * Inul + Ipnul;
		fact -= xi;
		Ipnul = fact * Inutemp + Inul;
		Inul = Inutemp;
	}
	T f = Ipnul / Inul;
	T Kmu, Knu1;
	if (x < x_min)
	{
		const T x2 = x / T(2);
		const T pimu = bksge::pi_t<T>() * mu;
		const T fact = (bksge::abs(pimu) < eps ? T(1) : pimu / bksge::sin(pimu));
		T d = -bksge::log(x2);
		T e = mu * d;
		const T fact2 = (bksge::abs(e) < eps ? T(1) : bksge::sinh(e) / e);
		T gam1, gam2, gampl, gammi;
		bksge::detail::gamma_temme(mu, gam1, gam2, gampl, gammi);
		T ff = fact * (gam1 * bksge::cosh(e) + gam2 * fact2 * d);
		T sum = ff;
		e = bksge::exp(e);
		T p = e / (T(2) * gampl);
		T q = T(1) / (T(2) * e * gammi);
		T c = T(1);
		d = x2 * x2;
		T sum1 = p;
		int i = 1;
		for (; i <= max_iter; ++i)
		{
			ff = (i * ff + p + q) / (i * i - mu2);
			c *= d / i;
			p /= i - mu;
			q /= i + mu;
			const T del = c * ff;
			sum += del;
			const T del1 = c * (p - i * ff);
			sum1 += del1;
			if (bksge::abs(del) < eps * bksge::abs(sum))
			{
				break;
			}
		}

		if (i > max_iter)
		{
			bksge::throw_runtime_error("Bessel k series failed to converge in bessel_ik.");
		}

		Kmu = sum;
		Knu1 = sum1 * xi2;
	}
	else
	{
		T b = T(2) * (T(1) + x);
		T d = T(1) / b;
		T delh = d;
		T h = delh;
		T q1 = T(0);
		T q2 = T(1);
		T a1 = T(0.25L) - mu2;
		T q = c = a1;
		T a = -a1;
		T s = T(1) + q * delh;
		int i = 2;
		for (; i <= max_iter; ++i)
		{
			a -= 2 * (i - 1);
			c = -a * c / i;
			const T qnew = (q1 - b * q2) / a;
			q1 = q2;
			q2 = qnew;
			q += c * qnew;
			b += T(2);
			d = T(1) / (b + a * d);
			delh = (b * d - T(1)) * delh;
			h += delh;
			const T dels = q * delh;
			s += dels;
			if (bksge::abs(dels / s) < eps)
			{
				break;
			}
		}

		if (i > max_iter)
		{
			bksge::throw_runtime_error("Steed's method failed in bessel_ik.");
		}

		h = a1 * h;
		Kmu = bksge::sqrt(bksge::pi_t<T>() / (T(2) * x)) * bksge::exp(-x) / s;
		Knu1 = Kmu * (mu + x + T(0.5L) - h) * xi;
	}

	T Kpmu = mu * xi * Kmu - Knu1;
	T Inumu = xi / (f * Kmu - Kpmu);
	Inu = Inumu * Inul1 / Inul;
	Ipnu = Inumu * Ipnu1 / Inul;
	for (i = 1; i <= nl; ++i)
	{
		const T Knutemp = (mu + i) * xi2 * Knu1 + Kmu;
		Kmu = Knu1;
		Knu1 = Knutemp;
	}
	Knu = Kmu;
	Kpnu = nu * xi * Kmu - Knu1;

	return;
}

BKSGE_WARNING_POP();

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_BESSEL_IK_HPP
