/**
 *	@file	tgamma.hpp
 *
 *	@brief	tgamma 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_TGAMMA_HPP
#define BKSGE_FND_CMATH_TGAMMA_HPP

#include <bksge/fnd/cmath/detail/tgamma_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ガンマ関数を計算します．
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x
 *
 *	@return	x のガンマ関数を返します。
 *
 *	x が ±0      の場合、+∞ を返す。
 *	x が 負の整数 の場合、NaN を返す。
 *	x が -∞      の場合、NaN を返す。
 *	x が +∞      の場合、+∞ を返す。
 *	x が NaN     の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
tgamma(float arg) BKSGE_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

inline BKSGE_CONSTEXPR float
tgammaf(float arg) BKSGE_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

inline BKSGE_CONSTEXPR double
tgamma(double arg) BKSGE_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

inline BKSGE_CONSTEXPR long double
tgamma(long double arg) BKSGE_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

inline BKSGE_CONSTEXPR long double
tgammal(long double arg) BKSGE_NOEXCEPT
{
	return detail::tgamma_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
tgamma(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::tgamma_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_TGAMMA_HPP
