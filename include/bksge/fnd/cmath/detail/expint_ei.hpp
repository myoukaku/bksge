/**
 *	@file	expint_ei.hpp
 *
 *	@brief	expint_Ei 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_EI_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_EI_HPP

#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/detail/expint_e1.hpp>
#include <bksge/fnd/cmath/detail/expint_ei_series.hpp>
#include <bksge/fnd/cmath/detail/expint_ei_asymp.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
BKSGE_CXX14_CONSTEXPR T expint_E1(T);

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
expint_Ei(T x)
{
	if (x < T(0))
	{
		return -bksge::detail::expint_E1(-x);
	}
	else if (x < -bksge::log(bksge::numeric_limits<T>::epsilon()))
	{
		return bksge::detail::expint_Ei_series(x);
	}
	else
	{
		return bksge::detail::expint_Ei_asymp(x);
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_EI_HPP
