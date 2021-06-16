/**
 *	@file	expm1.hpp
 *
 *	@brief	expm1 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_EXPM1_HPP
#define BKSGE_FND_CMATH_EXPM1_HPP

#include <bksge/fnd/cmath/detail/expm1_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	e (ネイピア数) を底とする指数関数から 1 を引いた値を求める。
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	e (ネイピア数) の x 乗から 1 を引いた値を返す。
 *
 *	x が ±0  の場合、±0 を返す。
 *	x が -∞  の場合、-1  を返す。
 *	x が +∞  の場合、+∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
expm1(float arg) BKSGE_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

inline BKSGE_CONSTEXPR float
expm1f(float arg) BKSGE_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

inline BKSGE_CONSTEXPR double
expm1(double arg) BKSGE_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

inline BKSGE_CONSTEXPR long double
expm1(long double arg) BKSGE_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

inline BKSGE_CONSTEXPR long double
expm1l(long double arg) BKSGE_NOEXCEPT
{
	return detail::expm1_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
expm1(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::expm1_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_EXPM1_HPP
