/**
 *	@file	lgamma.hpp
 *
 *	@brief	lgamma 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LGAMMA_HPP
#define BKSGE_FND_CMATH_LGAMMA_HPP

#include <bksge/fnd/cmath/detail/lgamma_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ガンマ関数の絶対値の自然対数 (loge) を計算します．
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x
 *
 *	@return	x のガンマ関数の絶対値の自然対数を返します。
 *
 *	x が 1       の場合、+0  を返す。
 *	x が 2       の場合、+0  を返す。
 *	x が ±0      の場合、+∞ を返す。
 *	x が 負の整数 の場合、+∞ を返す。
 *	x が ±∞      の場合、+∞ を返す。
 *	x が NaN     の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
lgamma(float arg) BKSGE_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

inline BKSGE_CONSTEXPR float
lgammaf(float arg) BKSGE_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

inline BKSGE_CONSTEXPR double
lgamma(double arg) BKSGE_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

inline BKSGE_CONSTEXPR long double
lgamma(long double arg) BKSGE_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

inline BKSGE_CONSTEXPR long double
lgammal(long double arg) BKSGE_NOEXCEPT
{
	return detail::lgamma_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
lgamma(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::lgamma_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LGAMMA_HPP
