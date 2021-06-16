/**
 *	@file	riemann_zeta_product.hpp
 *
 *	@brief	riemann_zeta_product 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_PRODUCT_HPP
#define BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_PRODUCT_HPP

#include <bksge/fnd/cmath/pow.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
riemann_zeta_product(T s)
{
	T const primes[] =
	{
		T(2), T(3), T(5), T(7), T(11), T(13), T(17), T(19),
		T(23), T(29), T(31), T(37), T(41), T(43), T(47),
		T(53), T(59), T(61), T(67), T(71), T(73), T(79),
		T(83), T(89), T(97), T(101), T(103), T(107), T(109)
	};

	T zeta = T(1);
	for (auto prime : primes)
	{
		T const fact = T(1) - bksge::pow(prime, -s);
		zeta *= fact;
		if (T(1) - fact < bksge::numeric_limits<T>::epsilon())
		{
			break;
		}
	}

	return T(1) / zeta;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RIEMANN_ZETA_PRODUCT_HPP
