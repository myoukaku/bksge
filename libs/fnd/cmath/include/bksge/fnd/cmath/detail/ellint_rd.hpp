/**
 *	@file	ellint_rd.hpp
 *
 *	@brief	ellint_rd 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ELLINT_RD_HPP
#define BKSGE_FND_CMATH_DETAIL_ELLINT_RD_HPP

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
ellint_rd(T x, T y, T z)
{
	T const eps = std::numeric_limits<T>::epsilon();
	T const errtol = bksge::pow(eps / T(8), T(1) / T(6));
	T const max = std::numeric_limits<T>::max();
	T const lolim = T(2) / bksge::pow(max, T(2) / T(3));

	if (x < T(0) || y < T(0))
	{
		//bksge::throw_domain_error("Argument less than zero in ellint_rd.");
		return std::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || z < lolim)
	{
		//bksge::throw_domain_error("Argument too small in ellint_rd.");
		return std::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(3) / T(14);
		T const c2 = T(1) / T(6);
		T const c3 = T(9) / T(22);
		T const c4 = T(3) / T(26);

		T xn = x;
		T yn = y;
		T zn = z;
		T sigma = T(0);
		T power4 = T(1);

		T mu;
		T xndev, yndev, zndev;

		const unsigned int max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + T(3) * zn) / T(5);
			xndev = (mu - xn) / mu;
			yndev = (mu - yn) / mu;
			zndev = (mu - zn) / mu;
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
			sigma += power4 / (znroot * (zn + lambda));
			power4 *= c0;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
		}

		T const ea = xndev * yndev;
		T const eb = zndev * zndev;
		T const ec = ea - eb;
		T const ed = ea - T(6) * eb;
		T const ef = ed + ec + ec;
		T const s1 = ed * (-c1 + c3 * ed / T(3) - T(3) * c4 * zndev * ef / T(2));
		T const s2 = zndev * (c2 * ef + zndev * (-c3 * ec - zndev * c4 - ea));

		return T(3) * sigma + power4 * (T(1) + s1 + s2) / (mu * bksge::sqrt(mu));
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ELLINT_RD_HPP
