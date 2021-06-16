/**
 *	@file	fabs.hpp
 *
 *	@brief	fabs 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FABS_HPP
#define BKSGE_FND_CMATH_FABS_HPP

#include <bksge/fnd/cmath/detail/fabs_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	絶対値を求める
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの絶対値を返す
 *
 *	x が ±0  の場合、+0  を返す。
 *	x が ±∞ の場合、+∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
fabs(float arg) BKSGE_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

inline BKSGE_CONSTEXPR float
fabsf(float arg) BKSGE_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

inline BKSGE_CONSTEXPR double
fabs(double arg) BKSGE_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

inline BKSGE_CONSTEXPR long double
fabs(long double arg) BKSGE_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

inline BKSGE_CONSTEXPR long double
fabsl(long double arg) BKSGE_NOEXCEPT
{
	return detail::fabs_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
fabs(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::fabs_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FABS_HPP
