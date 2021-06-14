/**
 *	@file	log10.hpp
 *
 *	@brief	log10 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOG10_HPP
#define BKSGE_FND_CMATH_LOG10_HPP

#include <bksge/fnd/cmath/detail/log10_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	10 を底とする常用対数を求める
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x の 10 を底とする常用対数
 *
 *	x が ±0  だった場合、-∞ を返す。
 *	x が 1   だった場合、+0  を返す。
 *	x < 0    だった場合、NaN を返す。
 *	x が +∞  だった場合、+∞ を返す。
 *	x が NaN だった場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
log10(float arg) BKSGE_NOEXCEPT
{
	return detail::log10_impl(arg);
}

inline BKSGE_CONSTEXPR float
log10f(float arg) BKSGE_NOEXCEPT
{
	return detail::log10_impl(arg);
}

inline BKSGE_CONSTEXPR double
log10(double arg) BKSGE_NOEXCEPT
{
	return detail::log10_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log10(long double arg) BKSGE_NOEXCEPT
{
	return detail::log10_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log10l(long double arg) BKSGE_NOEXCEPT
{
	return detail::log10_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
log10(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::log10_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LOG10_HPP
