/**
 *	@file	cosh.hpp
 *
 *	@brief	cosh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COSH_HPP
#define BKSGE_FND_CMATH_COSH_HPP

#include <bksge/fnd/cmath/detail/cosh_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	双曲線余弦（ハイパボリックコサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの双曲線余弦を返す
 *
 *	arg が ±0  の場合、1を返す。
 *	arg が ±∞ の場合、+∞を返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
cosh(float arg) BKSGE_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

inline BKSGE_CONSTEXPR float
coshf(float arg) BKSGE_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

inline BKSGE_CONSTEXPR double
cosh(double arg) BKSGE_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
cosh(long double arg) BKSGE_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
coshl(long double arg) BKSGE_NOEXCEPT
{
	return detail::cosh_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
cosh(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::cosh_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_COSH_HPP
