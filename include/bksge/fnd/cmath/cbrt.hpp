/**
 *	@file	cbrt.hpp
 *
 *	@brief	cbrt 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_CBRT_HPP
#define BKSGE_FND_CMATH_CBRT_HPP

#include <bksge/fnd/cmath/detail/cbrt_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	立方根を取得する
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの立方根を返す
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0 の場合、xをそのまま返す。
 *	x が NaN の場合、NaNを返す。
 *
 *	@note	cbrt(x) は pow(x, 1.0 / 3.0) と違い、
 *			xが負の値でも立方根を計算できる。
 */
inline BKSGE_CONSTEXPR float
cbrt(float arg) BKSGE_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

inline BKSGE_CONSTEXPR float
cbrtf(float arg) BKSGE_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

inline BKSGE_CONSTEXPR double
cbrt(double arg) BKSGE_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

inline BKSGE_CONSTEXPR long double
cbrt(long double arg) BKSGE_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

inline BKSGE_CONSTEXPR long double
cbrtl(long double arg) BKSGE_NOEXCEPT
{
	return detail::cbrt_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
cbrt(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::cbrt_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_CBRT_HPP
