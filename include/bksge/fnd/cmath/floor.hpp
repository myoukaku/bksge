/**
 *	@file	floor.hpp
 *
 *	@brief	floor 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FLOOR_HPP
#define BKSGE_FND_CMATH_FLOOR_HPP

#include <bksge/fnd/cmath/detail/floor_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	床関数
 *
 *	@param	arg	対象となる値
 *
 *	@return	arg以下で最大の整数
 *
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
floor(float arg) BKSGE_NOEXCEPT
{
	return detail::floor_impl(arg);
}

inline BKSGE_CONSTEXPR float
floorf(float arg) BKSGE_NOEXCEPT
{
	return detail::floor_impl(arg);
}

inline BKSGE_CONSTEXPR double
floor(double arg) BKSGE_NOEXCEPT
{
	return detail::floor_impl(arg);
}

inline BKSGE_CONSTEXPR long double
floor(long double arg) BKSGE_NOEXCEPT
{
	return detail::floor_impl(arg);
}

inline BKSGE_CONSTEXPR long double
floorl(long double arg) BKSGE_NOEXCEPT
{
	return detail::floor_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
floor(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::floor_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FLOOR_HPP
