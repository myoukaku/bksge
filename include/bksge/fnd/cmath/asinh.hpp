/**
 *	@file	asinh.hpp
 *
 *	@brief	asinh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ASINH_HPP
#define BKSGE_FND_CMATH_ASINH_HPP

#include <bksge/fnd/cmath/detail/asinh_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	逆双曲線正弦（アークハイパボリックサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの逆双曲線正弦を返す
 *
 *	arg が ±0  の場合、arg をそのまま返す。
 *	arg が ±∞ の場合、arg をそのまま返す。
 *	arg が NaN  の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
asinh(float arg) BKSGE_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

inline BKSGE_CONSTEXPR float
asinhf(float arg) BKSGE_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

inline BKSGE_CONSTEXPR double
asinh (double arg) BKSGE_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
asinh (long double arg) BKSGE_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
asinhl(long double arg) BKSGE_NOEXCEPT
{
	return detail::asinh_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
asinh(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::asinh_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ASINH_HPP
