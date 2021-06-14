/**
 *	@file	log.hpp
 *
 *	@brief	log 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOG_HPP
#define BKSGE_FND_CMATH_LOG_HPP

#include <bksge/fnd/cmath/detail/log_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	e (ネイピア数) を底とする自然対数を求める
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の e (ネイピア数) を底とする自然対数
 *
 *	arg が ±0 だった場合、-∞ を返す。
 *	arg が 1   だった場合、+0  を返す。
 *	arg < 0    だった場合、NaN を返す。
 *	arg が +∞ だった場合、+∞ を返す。
 *	arg が NaN だった場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
log(float arg) BKSGE_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline BKSGE_CONSTEXPR float
logf(float arg) BKSGE_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline BKSGE_CONSTEXPR double
log(double arg) BKSGE_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log(long double arg) BKSGE_NOEXCEPT
{
	return detail::log_impl(arg);
}

inline BKSGE_CONSTEXPR long double
logl(long double arg) BKSGE_NOEXCEPT
{
	return detail::log_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
log(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::log_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LOG_HPP
