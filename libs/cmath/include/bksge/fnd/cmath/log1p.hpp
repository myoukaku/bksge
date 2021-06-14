/**
 *	@file	log1p.hpp
 *
 *	@brief	log1p 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOG1P_HPP
#define BKSGE_FND_CMATH_LOG1P_HPP

#include <bksge/fnd/cmath/detail/log1p_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	引数に 1 を足した値の、e (ネイピア数) を底とする自然対数を求める。
 *
 *	@param	arg
 *
 *	@return	引数 arg に対して 1+arg の e (ネイピア数) を底とする自然対数を返す。
 *
 *	arg が ±0    の場合、±0 を返す。
 *	arg が -1     の場合、-∞ を返す。
 *	arg が -1未満 の場合、NaN を返す。
 *	arg が +∞    の場合、+∞ を返す。
 *	arg が NaN    の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
log1p(float arg) BKSGE_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

inline BKSGE_CONSTEXPR float
log1pf(float arg) BKSGE_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

inline BKSGE_CONSTEXPR double
log1p(double arg) BKSGE_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log1p(long double arg) BKSGE_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

inline BKSGE_CONSTEXPR long double
log1pl(long double arg) BKSGE_NOEXCEPT
{
	return detail::log1p_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
log1p(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::log1p_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LOG1P_HPP
