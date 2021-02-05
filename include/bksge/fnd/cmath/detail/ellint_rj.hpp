/**
 *	@file	ellint_rj.hpp
 *
 *	@brief	ellint_rj 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ELLINT_RJ_HPP
#define BKSGE_FND_CMATH_DETAIL_ELLINT_RJ_HPP

#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/detail/ellint_rc.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
ellint_rj(T x, T y, T z, T p)
{
	T const min = bksge::numeric_limits<T>::min();
	T const lolim = bksge::pow(T(5) * min, T(1) / T(3));

	if (x < T(0) || y < T(0) || z < T(0))
	{
		//bksge::throw_domain_error("Argument less than zero in ellint_rj.");
		return bksge::numeric_limits<T>::quiet_NaN();
	}
	else if (x + y < lolim || x + z < lolim || y + z < lolim || p < lolim)
	{
		//bksge::throw_domain_error("Argument too small in ellint_rj");
		return bksge::numeric_limits<T>::quiet_NaN();
	}
	else
	{
		T const c0 = T(1) / T(4);
		T const c1 = T(3) / T(14);
		T const c2 = T(1) / T(3);
		T const c3 = T(3) / T(22);
		T const c4 = T(3) / T(26);

		T xn = x;
		T yn = y;
		T zn = z;
		T pn = p;
		T sigma = T(0);
		T power4 = T(1);

		T const eps = bksge::numeric_limits<T>::epsilon();
		T const errtol = bksge::pow(eps / T(8), T(1) / T(6));

		T mu;
		T xndev, yndev, zndev, pndev;

		unsigned int const max_iter = 100;
		for (unsigned int iter = 0; iter < max_iter; ++iter)
		{
			mu = (xn + yn + zn + T(2) * pn) / T(5);
			xndev = (mu - xn) / mu;
			yndev = (mu - yn) / mu;
			zndev = (mu - zn) / mu;
			pndev = (mu - pn) / mu;
			T const epsilon = bksge::max({
				bksge::abs(xndev),
				bksge::abs(yndev),
				bksge::abs(zndev),
				bksge::abs(pndev)});
			if (epsilon < errtol)
			{
				break;
			}
			T const xnroot = bksge::sqrt(xn);
			T const ynroot = bksge::sqrt(yn);
			T const znroot = bksge::sqrt(zn);
			T const lambda = xnroot * (ynroot + znroot) + ynroot * znroot;
			T const alpha1 = pn * (xnroot + ynroot + znroot) + xnroot * ynroot * znroot;
			T const alpha2 = alpha1 * alpha1;
			T const beta = pn * (pn + lambda) * (pn + lambda);
			sigma += power4 * bksge::detail::ellint_rc(alpha2, beta);
			power4 *= c0;
			xn = c0 * (xn + lambda);
			yn = c0 * (yn + lambda);
			zn = c0 * (zn + lambda);
			pn = c0 * (pn + lambda);
		}

		T const ea = xndev * (yndev + zndev) + yndev * zndev;
		T const eb = xndev * yndev * zndev;
		T const ec = pndev * pndev;
		T const e2 = ea - T(3) * ec;
		T const e3 = eb + T(2) * pndev * (ea - ec);
		T const s1 = T(1) + e2 * (-c1 + T(3) * c3 * e2 / T(4) - T(3) * c4 * e3 / T(2));
		T const s2 = eb * (c2 / T(2) + pndev * (-c3 - c3 + pndev * c4));
		T const s3 = pndev * ea * (c2 - pndev * c3) - c2 * pndev * ec;

		return T(3) * sigma + power4 * (s1 + s2 + s3) / (mu * bksge::sqrt(mu));
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ELLINT_RJ_HPP
