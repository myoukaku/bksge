/**
 *	@file	ellint_rc.hpp
 *
 *	@brief	ellint_rc 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ELLINT_RC_HPP
#define BKSGE_FND_CMATH_DETAIL_ELLINT_RC_HPP

#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_rc(T x, T y)
{
	T const lolim = T(5) * bksge::numeric_limits<T>::min();

	if (x < T(0) || y < T(0) || x + y < lolim)
	{
		//bksge::throw_domain_error("Argument less than zero in __ellint_rc.");
		return bksge::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(1) / T(7);
		T const c2 = T(9) / T(22);
		T const c3 = T(3) / T(10);
		T const c4 = T(3) / T(8);

		T xn = x;
		T yn = y;

		T const eps = bksge::numeric_limits<T>::epsilon();
		T const errtol = bksge::pow(eps / T(30), T(1) / T(6));
		T mu;
		T sn;

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + T(2) * yn) / T(3);
			sn = (yn + mu) / mu - T(2);
			if (bksge::abs(sn) < errtol)
			{
				break;
			}
			T const lambda = T(2) * bksge::sqrt(xn) * bksge::sqrt(yn) + yn;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
		}

		T const s = sn * sn * (c3 + sn*(c1 + sn * (c4 + sn * c2)));

		return (T(1) + s) / bksge::sqrt(mu);
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ELLINT_RC_HPP
