/**
 *	@file	expint_ei_series.hpp
 *
 *	@brief	expint_Ei_series 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_EI_SERIES_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_EI_SERIES_HPP

#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_Ei_series(T x)
{
	T term = T(1);
	T sum = T(0);
	unsigned int const max_iter = 1000;
	for (unsigned int i = 1; i < max_iter; ++i)
	{
		term *= x / i;
		sum += term / i;
		if (term < std::numeric_limits<T>::epsilon() * sum)
		{
			break;
		}
	}

	return bksge::egamma_t<T>() + sum + bksge::log(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_EI_SERIES_HPP
