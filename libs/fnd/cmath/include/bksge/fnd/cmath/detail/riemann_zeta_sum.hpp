/**
 *	@file	riemann_zeta_sum.hpp
 *
 *	@brief	riemann_zeta_sum 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_SUM_HPP
#define BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_SUM_HPP

#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/stdexcept/domain_error.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
riemann_zeta_sum(T s)
{
	//  A user shouldn't get to this.
	if (s < T(1))
	{
		bksge::throw_domain_error("Bad argument in zeta sum.");
	}

	unsigned int const max_iter = 10000;
	T zeta = T(0);
	for (unsigned int k = 1; k < max_iter; ++k)
	{
		T term = bksge::pow(static_cast<T>(k), -s);
		if (term < std::numeric_limits<T>::epsilon())
		{
			break;
		}
		zeta += term;
	}

	return zeta;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_SUM_HPP
