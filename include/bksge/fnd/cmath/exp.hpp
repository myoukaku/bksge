/**
 *	@file	exp.hpp
 *
 *	@brief	exp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_EXP_HPP
#define BKSGE_FND_CMATH_EXP_HPP

#include <bksge/fnd/cmath/detail/exp_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	e (ネイピア数) を底とする指数関数を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、e (ネイピア数) の arg 乗を返す。
 *
 *	arg が ±0  の場合、1  を返す。
 *	arg が -∞  の場合、+0 を返す。
 *	arg が +∞  の場合、+∞ を返す。
 *	arg が NaN  の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
exp(float arg) BKSGE_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline BKSGE_CONSTEXPR float
expf(float arg) BKSGE_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline BKSGE_CONSTEXPR double
exp(double arg) BKSGE_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline BKSGE_CONSTEXPR long double
exp(long double arg) BKSGE_NOEXCEPT
{
	return detail::exp_impl(arg);
}

inline BKSGE_CONSTEXPR long double
expl(long double arg) BKSGE_NOEXCEPT
{
	return detail::exp_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
exp(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::exp_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_EXP_HPP
