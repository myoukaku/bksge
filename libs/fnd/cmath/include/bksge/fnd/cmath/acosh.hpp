/**
 *	@file	acosh.hpp
 *
 *	@brief	acosh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ACOSH_HPP
#define BKSGE_FND_CMATH_ACOSH_HPP

#include <bksge/fnd/cmath/detail/acosh_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	逆双曲線余弦（アークハイパボリックコサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの逆双曲線余弦を返す
 *
 *	arg < 1  の場合、NaN を返す。
 *	arg = 1  の場合、+0  を返す。
 *	arg が +∞ の場合、+∞ を返す。
 *	arg が NaN の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
acosh(float arg) BKSGE_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

inline BKSGE_CONSTEXPR float
acoshf(float arg) BKSGE_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

inline BKSGE_CONSTEXPR double
acosh (double arg) BKSGE_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
acosh (long double arg) BKSGE_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
acoshl(long double arg) BKSGE_NOEXCEPT
{
	return detail::acosh_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
acosh(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::acosh_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ACOSH_HPP
