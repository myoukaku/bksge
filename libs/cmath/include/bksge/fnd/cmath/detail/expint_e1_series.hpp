/**
 *	@file	expint_e1_series.hpp
 *
 *	@brief	expint_E1_series 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_E1_SERIES_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_E1_SERIES_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_E1_series(T x)
{
	T const eps = bksge::numeric_limits<T>::epsilon();
	T term = T(1);
	T esum = T(0);
	T osum = T(0);
	unsigned int const max_iter = 1000;
	for (unsigned int i = 1; i < max_iter; ++i)
	{
		term *= -x / i;
		if (bksge::abs(term) < eps)
		{
			break;
		}

		if (term >= T(0))
		{
			esum += term / i;
		}
		else
		{
			osum += term / i;
		}
	}

	return -esum - osum - bksge::egamma_t<T>() - bksge::log(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_E1_SERIES_HPP
