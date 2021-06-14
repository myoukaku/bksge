/**
 *	@file	log2.hpp
 *
 *	@brief	log2 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOG2_HPP
#define BKSGE_FND_CMATH_LOG2_HPP

#include <bksge/fnd/cmath/detail/log2_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	2 を底とする二進対数を求める
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x の 2 を底とする二進対数
 *
 *	x が ±0  だった場合、-∞ を返す。
 *	x が 1   だった場合、+0  を返す。
 *	x < 0    だった場合、NaN を返す。
 *	x が +∞  だった場合、+∞ を返す。
 *	x が NaN だった場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
log2(float arg) BKSGE_NOEXCEPT
{
	return detail::log2_impl(arg);
}

inline BKSGE_CONSTEXPR float
log2f(float arg) BKSGE_NOEXCEPT
{
	return detail::log2_impl(arg);
}

inline BKSGE_CONSTEXPR double
log2(double arg) BKSGE_NOEXCEPT
{
	return detail::log2_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log2(long double arg) BKSGE_NOEXCEPT
{
	return detail::log2_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log2l(long double arg) BKSGE_NOEXCEPT
{
	return detail::log2_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
log2(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::log2_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LOG2_HPP
