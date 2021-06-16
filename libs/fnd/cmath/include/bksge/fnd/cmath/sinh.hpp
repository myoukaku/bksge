/**
 *	@file	sinh.hpp
 *
 *	@brief	sinh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SINH_HPP
#define BKSGE_FND_CMATH_SINH_HPP

#include <bksge/fnd/cmath/detail/sinh_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	双曲線正弦（ハイパボリックサイン）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの双曲線正弦を返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
sinh(float arg) BKSGE_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

inline BKSGE_CONSTEXPR float
sinhf(float arg) BKSGE_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

inline BKSGE_CONSTEXPR double
sinh(double arg) BKSGE_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
sinh(long double arg) BKSGE_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
sinhl(long double arg) BKSGE_NOEXCEPT
{
	return detail::sinh_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
sinh(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::sinh_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SINH_HPP
