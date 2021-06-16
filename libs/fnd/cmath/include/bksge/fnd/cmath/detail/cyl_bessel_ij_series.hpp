/**
 *	@file	cyl_bessel_ij_series.hpp
 *
 *	@brief	cyl_bessel_ij_series 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_IJ_SERIES_HPP
#define BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_IJ_SERIES_HPP

#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/lgamma.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
cyl_bessel_ij_series(T nu, T x, T sgn, unsigned int max_iter)
{
	if (x == T(0))
	{
		return nu == T(0) ? T(1) : T(0);
	}

	const T x2 = x / T(2);
	T fact = nu * bksge::log(x2);
	fact -= bksge::lgamma(nu + T(1));
	fact = bksge::exp(fact);
	const T xx4 = sgn * x2 * x2;
	T Jn = T(1);
	T term = T(1);

	for (unsigned int i = 1; i < max_iter; ++i)
	{
		term *= xx4 / (T(i) * (nu + T(i)));
		Jn += term;
		if (bksge::abs(term / Jn) < bksge::numeric_limits<T>::epsilon())
		{
			break;
		}
	}

	return fact * Jn;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CYL_BESSEL_IJ_SERIES_HPP
