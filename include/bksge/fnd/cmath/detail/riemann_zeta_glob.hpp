/**
 *	@file	riemann_zeta_glob.hpp
 *
 *	@brief	riemann_zeta_glob 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_GLOB_HPP
#define BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_GLOB_HPP

#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/fmod.hpp>
#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/lgamma.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
riemann_zeta_glob(T s)
{
	T const eps = bksge::numeric_limits<T>::epsilon();
	//  Max e exponent before overflow.
	T const max_bincoeff = bksge::numeric_limits<T>::max_exponent10 * bksge::log(T(10)) - T(1);

	//  This series works until the binomial coefficient blows up
	//  so use reflection.
	if (s < T(0))
	{
		if (bksge::fmod(s, T(2)) == T(0))
		{
			return T(0);
		}
		else
		{
			return
				riemann_zeta_glob(T(1) - s) *
				bksge::pow(T(2) *
				bksge::pi_t<T>(), s) *
				bksge::sin((bksge::pi_t<T>() / 2) * s) *
				bksge::exp(bksge::lgamma(T(1) - s)) /
				bksge::pi_t<T>();
		}
	}

	T zeta = T(0);
	T num = T(0.5L);
	unsigned int const maxit = 10000;
	for (unsigned int i = 0; i < maxit; ++i)
	{
		bool punt = false;
		T sgn = T(1);
		T term = T(0);
		for (unsigned int j = 0; j <= i; ++j)
		{
			T const bincoeff =
				bksge::lgamma(T(1 + i)) -
				bksge::lgamma(T(1 + j)) -
				bksge::lgamma(T(1 + i - j));

			if (bincoeff > max_bincoeff)
			{
				//  This only gets hit for x << 0.
				punt = true;
				break;
			}

			term += sgn * bksge::exp(bincoeff) * bksge::pow(T(1 + j), -s);
			sgn *= T(-1);
		}

		if (punt)
		{
			break;
		}

		term *= num;
		zeta += term;
		if (bksge::abs(term/zeta) < eps)
		{
			break;
		}

		num *= T(0.5L);
	}

	return zeta / (T(1) - bksge::pow(T(2), T(1) - s));
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_GLOB_HPP
