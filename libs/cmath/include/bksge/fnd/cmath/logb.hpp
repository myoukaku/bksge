/**
 *	@file	logb.hpp
 *
 *	@brief	logb 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOGB_HPP
#define BKSGE_FND_CMATH_LOGB_HPP

#include <bksge/fnd/cmath/detail/logb_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	浮動小数点数の指数部を返す
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の 指数部
 *
 *	arg が ±0  だった場合、-∞ を返す。
 *	arg が ±∞  だった場合、+∞ を返す。
 *	arg が NaN だった場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
logb(float arg) BKSGE_NOEXCEPT
{
	return detail::logb_impl(arg);
}

inline BKSGE_CONSTEXPR float
logbf(float arg) BKSGE_NOEXCEPT
{
	return detail::logb_impl(arg);
}

inline BKSGE_CONSTEXPR double
logb(double arg) BKSGE_NOEXCEPT
{
	return detail::logb_impl(arg);
}

inline BKSGE_CONSTEXPR long double
logb(long double arg) BKSGE_NOEXCEPT
{
	return detail::logb_impl(arg);
}

inline BKSGE_CONSTEXPR long double
logbl(long double arg) BKSGE_NOEXCEPT
{
	return detail::logb_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
logb(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::logb_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LOGB_HPP
