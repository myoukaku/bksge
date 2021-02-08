/**
 *	@file	expint_e1.hpp
 *
 *	@brief	expint_E1 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_E1_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_E1_HPP

#include <bksge/fnd/cmath/detail/expint_ei.hpp>
#include <bksge/fnd/cmath/detail/expint_e1_series.hpp>
#include <bksge/fnd/cmath/detail/expint_en_cont_frac.hpp>
#include <bksge/fnd/cmath/detail/expint_e1_asymp.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
BKSGE_CXX14_CONSTEXPR T expint_Ei(T);

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_E1(T x)
{
	if (x < T(0))
	{
		return -bksge::detail::expint_Ei(-x);
	}
	else if (x < T(1))
	{
		return bksge::detail::expint_E1_series(x);
	}
	else if (x < T(100))  //  TODO: Find a good asymptotic switch point.
	{
		return bksge::detail::expint_En_cont_frac(1, x);
	}
	else
	{
		return bksge::detail::expint_E1_asymp(x);
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_E1_HPP
