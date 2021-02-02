/**
 *	@file	ilogb.hpp
 *
 *	@brief	ilogb 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ILOGB_HPP
#define BKSGE_FND_CMATH_ILOGB_HPP

#include <bksge/fnd/cmath/detail/ilogb_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>
#include <climits>
#include <cmath>

namespace bksge
{

#if !defined(FP_ILOGB0)
#	define FP_ILOGB0	INT_MIN
#endif

#if !defined(FP_ILOGBNAN)
#	define FP_ILOGBNAN	INT_MAX
#endif

/**
 *	@brief	浮動小数点数の指数部をintとして返す
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の 指数部
 *
 *	arg が ±0  だった場合、FP_ILOGB0   を返す。
 *	arg が ±∞  だった場合、INT_MAX     を返す。
 *	arg が NaN だった場合、FP_ILOGBNAN を返す。
 */
inline BKSGE_CONSTEXPR int
ilogb(float arg) BKSGE_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

inline BKSGE_CONSTEXPR int
ilogbf(float arg) BKSGE_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

inline BKSGE_CONSTEXPR int
ilogb(double arg) BKSGE_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

inline BKSGE_CONSTEXPR int
ilogb(long double arg) BKSGE_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

inline BKSGE_CONSTEXPR int
ilogbl(long double arg) BKSGE_NOEXCEPT
{
	return detail::ilogb_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR int
ilogb(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::ilogb_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ILOGB_HPP
