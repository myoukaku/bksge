/**
 *	@file	ellint_rf.hpp
 *
 *	@brief	ellint_rf 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ELLINT_RF_HPP
#define BKSGE_FND_CMATH_DETAIL_ELLINT_RF_HPP

#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_rf(T x, T y, T z)
{
	T const lolim = T(5) * std::numeric_limits<T>::min();

	if (x < T(0) || y < T(0) || z < T(0))
	{
		//bksge::throw_domain_error("Argument less than zero in ellint_rf.");
		return std::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || x + z < lolim || y + z < lolim)
	{
		//bksge::throw_domain_error("Argument too small in ellint_rf");
		return std::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(1) / T(24);
		T const c2 = T(1) / T(10);
		T const c3 = T(3) / T(44);
		T const c4 = T(1) / T(14);

		T xn = x;
		T yn = y;
		T zn = z;

		T const eps = std::numeric_limits<T>::epsilon();
		T const errtol = bksge::pow(eps, T(1) / T(6));
		T mu;
		T xndev, yndev, zndev;

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + zn) / T(3);
			xndev = 2 - (mu + xn) / mu;
			yndev = 2 - (mu + yn) / mu;
			zndev = 2 - (mu + zn) / mu;
			T const epsilon = bksge::max(
				{bksge::abs(xndev), bksge::abs(yndev), bksge::abs(zndev)});
			if (epsilon < errtol)
			{
				break;
			}
			T const xnroot = bksge::sqrt(xn);
			T const ynroot = bksge::sqrt(yn);
			T const znroot = bksge::sqrt(zn);
			T const lambda = xnroot * (ynroot + znroot) + ynroot * znroot;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
		}

		T const e2 = xndev * yndev - zndev * zndev;
		T const e3 = xndev * yndev * zndev;
		T const s  = T(1) + (c1 * e2 - c2 - c3 * e3) * e2 + c4 * e3;

		return s / bksge::sqrt(mu);
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ELLINT_RF_HPP
