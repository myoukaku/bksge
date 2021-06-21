/**
 *	@file	bessel_jn.hpp
 *
 *	@brief	bessel_jn 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_BESSEL_JN_HPP
#define BKSGE_FND_CMATH_DETAIL_BESSEL_JN_HPP

#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/sinh.hpp>
#include <bksge/fnd/cmath/cosh.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/detail/gamma_temme.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/algorithm/max.hpp>
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
bessel_jn(T nu, T x, T& Jnu, T& Nnu, T& Jpnu, T& Npnu)
{
	if (x == T(0))
	{
		if (nu == T(0))
		{
			Jnu = T(1);
			Jpnu = T(0);
		}
		else if (nu == T(1))
		{
			Jnu = T(0);
			Jpnu = T(0.5L);
		}
		else
		{
			Jnu = T(0);
			Jpnu = T(0);
		}
		Nnu = -std::numeric_limits<T>::infinity();
		Npnu = std::numeric_limits<T>::infinity();
		return;
	}

	const T eps = std::numeric_limits<T>::epsilon();
	//  When the multiplier is N i.e.
	//  fp_min = N * min()
	//  Then J_0 and N_0 tank at x = 8 * N (J_0 = 0 and N_0 = nan)!
	//const T fp_min = T(20) * std::numeric_limits<T>::min();
	const T fp_min = bksge::sqrt(std::numeric_limits<T>::min());
	const int max_iter = 15000;
	const T x_min = T(2);

	const int nl = (x < x_min
		? static_cast<int>(nu + T(0.5L))
		: bksge::max(0, static_cast<int>(nu - x + T(1.5L))));

	const T mu = nu - nl;
	const T mu2 = mu * mu;
	const T xi = T(1) / x;
	const T xi2 = T(2) * xi;
	T w = xi2 / bksge::pi_t<T>();
	int isign = 1;
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
		d = b - d;
		if (bksge::abs(d) < fp_min)
		{
			d = fp_min;
		}
		c = b - T(1) / c;
		if (bksge::abs(c) < fp_min)
		{
			c = fp_min;
		}
		d = T(1) / d;
		const T del = c * d;
		h *= del;
		if (d < T(0))
		{
			isign = -isign;
		}
		if (bksge::abs(del - T(1)) < eps)
		{
			break;
		}
	}

	if (i > max_iter)
	{
		bksge::throw_runtime_error("Argument x too large in bessel_jn; try asymptotic expansion.");
	}

	T Jnul = isign * fp_min;
	T Jpnul = h * Jnul;
	T Jnul1 = Jnul;
	T Jpnu1 = Jpnul;
	T fact = nu * xi;
	for (int l = nl; l >= 1; --l)
	{
		const T Jnutemp = fact * Jnul + Jpnul;
		fact -= xi;
		Jpnul = fact * Jnutemp - Jnul;
		Jnul = Jnutemp;
	}
	if (Jnul == T(0))
	{
		Jnul = eps;
	}
	T f = Jpnul / Jnul;
	T Nmu, Nnu1, Npmu, Jmu;
	if (x < x_min)
	{
		const T x2 = x / T(2);
		const T pimu = bksge::pi_t<T>() * mu;
		T fact = (bksge::abs(pimu) < eps ? T(1) : pimu / bksge::sin(pimu));
		T d = -bksge::log(x2);
		T e = mu * d;
		T fact2 = (bksge::abs(e) < eps ? T(1) : bksge::sinh(e) / e);
		T gam1, gam2, gampl, gammi;
		bksge::detail::gamma_temme(mu, gam1, gam2, gampl, gammi);
		T ff = (T(2) / bksge::pi_t<T>()) * fact * (gam1 * bksge::cosh(e) + gam2 * fact2 * d);
		e = bksge::exp(e);
		T p = e / (bksge::pi_t<T>() * gampl);
		T q = T(1) / (e * bksge::pi_t<T>() * gammi);
		const T pimu2 = pimu / T(2);
		T fact3 = (bksge::abs(pimu2) < eps ? T(1) : bksge::sin(pimu2) / pimu2);
		T r = bksge::pi_t<T>() * pimu2 * fact3 * fact3;
		T c = T(1);
		d = -x2 * x2;
		T sum = ff + r * q;
		T sum1 = p;
		for (i = 1; i <= max_iter; ++i)
		{
			ff = (i * ff + p + q) / (i * i - mu2);
			c *= d / T(i);
			p /= T(i) - mu;
			q /= T(i) + mu;
			const T del = c * (ff + r * q);
			sum += del;
			const T del1 = c * p - i * del;
			sum1 += del1;
			if (bksge::abs(del) < eps * (T(1) + bksge::abs(sum)))
			{
				break;
			}
		}
		if (i > max_iter)
		{
			bksge::throw_runtime_error("Bessel y series failed to converge in bessel_jn.");
		}
		Nmu = -sum;
		Nnu1 = -sum1 * xi2;
		Npmu = mu * xi * Nmu - Nnu1;
		Jmu = w / (Npmu - f * Nmu);
	}
	else
	{
		T a = T(0.25L) - mu2;
		T q = T(1);
		T p = -xi / T(2);
		T br = T(2) * x;
		T bi = T(2);
		T fact = a * xi / (p * p + q * q);
		T cr = br + q * fact;
		T ci = bi + p * fact;
		T den = br * br + bi * bi;
		T dr = br / den;
		T di = -bi / den;
		T dlr = cr * dr - ci * di;
		T dli = cr * di + ci * dr;
		T temp = p * dlr - q * dli;
		q = p * dli + q * dlr;
		p = temp;
		int i = 2;
		for (; i <= max_iter; ++i)
		{
			a += T(2 * (i - 1));
			bi += T(2);
			dr = a * dr + br;
			di = a * di + bi;
			if (bksge::abs(dr) + bksge::abs(di) < fp_min)
			{
				dr = fp_min;
			}
			fact = a / (cr * cr + ci * ci);
			cr = br + cr * fact;
			ci = bi - ci * fact;
			if (bksge::abs(cr) + bksge::abs(ci) < fp_min)
			{
				cr = fp_min;
			}
			den = dr * dr + di * di;
			dr /= den;
			di /= -den;
			dlr = cr * dr - ci * di;
			dli = cr * di + ci * dr;
			temp = p * dlr - q * dli;
			q = p * dli + q * dlr;
			p = temp;
			if (bksge::abs(dlr - T(1)) + bksge::abs(dli) < eps)
			{
				break;
			}
		}
		if (i > max_iter)
		{
			bksge::throw_runtime_error("Lentz's method failed in bessel_jn.");
		}
		const T gam = (p - f) / q;
		Jmu = bksge::sqrt(w / ((p - f) * gam + q));
		Jmu = bksge::copysign(Jmu, Jnul);
		Nmu = gam * Jmu;
		Npmu = (p + q / gam) * Nmu;
		Nnu1 = mu * xi * Nmu - Npmu;
	}
	fact = Jmu / Jnul;
	Jnu = fact * Jnul1;
	Jpnu = fact * Jpnu1;
	for (i = 1; i <= nl; ++i)
	{
		const T Nnutemp = (mu + i) * xi2 * Nnu1 - Nmu;
		Nmu = Nnu1;
		Nnu1 = Nnutemp;
	}
	Nnu = Nmu;
	Npnu = nu * xi * Nmu - Nnu1;

	return;
}

BKSGE_WARNING_POP();

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_BESSEL_JN_HPP
