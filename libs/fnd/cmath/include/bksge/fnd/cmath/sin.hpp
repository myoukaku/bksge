/**
 *	@file	sin.hpp
 *
 *	@brief	sin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SIN_HPP
#define BKSGE_FND_CMATH_SIN_HPP

#include <bksge/fnd/cmath/detail/sin_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	正弦（サイン）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argのサインを返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
sin(float arg) BKSGE_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline BKSGE_CONSTEXPR float
sinf(float arg) BKSGE_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline BKSGE_CONSTEXPR double
sin(double arg) BKSGE_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline BKSGE_CONSTEXPR long double
sin(long double arg) BKSGE_NOEXCEPT
{
	return detail::sin_impl(arg);
}

inline BKSGE_CONSTEXPR long double
sinl(long double arg) BKSGE_NOEXCEPT
{
	return detail::sin_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
sin(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::sin_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SIN_HPP
