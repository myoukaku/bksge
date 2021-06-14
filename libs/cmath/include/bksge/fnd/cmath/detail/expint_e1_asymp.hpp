/**
 *	@file	expint_e1_asymp.hpp
 *
 *	@brief	expint_E1_asymp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_E1_ASYMP_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_E1_ASYMP_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_E1_asymp(T x)
{
	T term = T(1);
	T esum = T(1);
	T osum = T(0);
	unsigned int const max_iter = 1000;
	for (unsigned int i = 1; i < max_iter; ++i)
	{
		T prev = term;
		term *= -(i / x);
		if (bksge::abs(term) > bksge::abs(prev))
		{
			break;
		}

		if (term >= T(0))
		{
			esum += term;
		}
		else
		{
			osum += term;
		}
	}

	return bksge::exp(-x) * (esum + osum) / x;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_E1_ASYMP_HPP
