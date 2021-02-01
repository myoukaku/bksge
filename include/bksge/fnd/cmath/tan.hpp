/**
 *	@file	tan.hpp
 *
 *	@brief	tan 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_TAN_HPP
#define BKSGE_FND_CMATH_TAN_HPP

#include <bksge/fnd/cmath/detail/tan_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	正接（タンジェント）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argの正接を返す
 *
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
tan(float arg) BKSGE_NOEXCEPT
{
	return detail::tan_impl(arg);
}

inline BKSGE_CONSTEXPR float
tanf(float arg) BKSGE_NOEXCEPT
{
	return detail::tan_impl(arg);
}

inline BKSGE_CONSTEXPR double
tan(double arg) BKSGE_NOEXCEPT
{
	return detail::tan_impl(arg);
}

inline BKSGE_CONSTEXPR long double
tan(long double arg) BKSGE_NOEXCEPT
{
	return detail::tan_impl(arg);
}

inline BKSGE_CONSTEXPR long double
tanl(long double arg) BKSGE_NOEXCEPT
{
	return detail::tan_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
tan(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::tan_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_TAN_HPP
