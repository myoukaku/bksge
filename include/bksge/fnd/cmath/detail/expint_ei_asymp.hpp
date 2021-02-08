/**
 *	@file	expint_ei_asymp.hpp
 *
 *	@brief	expint_Ei_asymp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_EI_ASYMP_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_EI_ASYMP_HPP

#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_Ei_asymp(T x)
{
	T term = T(1);
	T sum = T(1);
	unsigned int const max_iter = 1000;
	for (unsigned int i = 1; i < max_iter; ++i)
	{
		T prev = term;
		term *= i / x;

		if (term < bksge::numeric_limits<T>::epsilon())
		{
			break;
		}

		if (term >= prev)
		{
			break;
		}

		sum += term;
	}

	return bksge::exp(x) * sum / x;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_EI_ASYMP_HPP
