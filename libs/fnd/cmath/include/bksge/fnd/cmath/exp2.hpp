/**
 *	@file	exp2.hpp
 *
 *	@brief	exp2 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_EXP2_HPP
#define BKSGE_FND_CMATH_EXP2_HPP

#include <bksge/fnd/cmath/detail/exp2_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	2 を底とする指数関数を求める
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、2 の x 乗を返す。
 *
 *	x が ±0  の場合、1  を返す。
 *	x が -∞  の場合、+0 を返す。
 *	x が +∞  の場合、+∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
exp2(float arg) BKSGE_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline BKSGE_CONSTEXPR float
exp2f(float arg) BKSGE_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline BKSGE_CONSTEXPR double
exp2(double arg) BKSGE_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline BKSGE_CONSTEXPR long double
exp2(long double arg) BKSGE_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

inline BKSGE_CONSTEXPR long double
exp2l(long double arg) BKSGE_NOEXCEPT
{
	return detail::exp2_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
exp2(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::exp2_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_EXP2_HPP
