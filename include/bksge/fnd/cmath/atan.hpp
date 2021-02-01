/**
 *	@file	atan.hpp
 *
 *	@brief	atan 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ATAN_HPP
#define BKSGE_FND_CMATH_ATAN_HPP

#include <bksge/fnd/cmath/detail/atan_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	アークタンジェントを取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argのアークタンジェントを返す
 *
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が +∞ の場合、+π/2 を返す。
 *	arg が -∞ の場合、-π/2 を返す。
 *	arg が NaN の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
atan(float arg) BKSGE_NOEXCEPT
{
	return detail::atan_impl(arg);
}

inline BKSGE_CONSTEXPR float
atanf(float arg) BKSGE_NOEXCEPT
{
	return detail::atan_impl(arg);
}

inline BKSGE_CONSTEXPR double
atan(double arg) BKSGE_NOEXCEPT
{
	return detail::atan_impl(arg);
}

inline BKSGE_CONSTEXPR long double
atan(long double arg) BKSGE_NOEXCEPT
{
	return detail::atan_impl(arg);
}

inline BKSGE_CONSTEXPR long double
atanl(long double arg) BKSGE_NOEXCEPT
{
	return detail::atan_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
atan(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::atan_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ATAN_HPP
