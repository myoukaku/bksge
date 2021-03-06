﻿/**
 *	@file	llrint.hpp
 *
 *	@brief	llrint 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LLRINT_HPP
#define BKSGE_FND_CMATH_LLRINT_HPP

#include <bksge/fnd/cmath/detail/llrint_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	現在の丸めモードで整数値に丸めた値を得る
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg を現在の丸めモードで整数値に丸めた値
 *
 *	arg が ±∞  の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR long long
llrint(float arg) BKSGE_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llrintf(float arg) BKSGE_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llrint(double arg) BKSGE_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llrint(long double arg) BKSGE_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llrintl(long double arg) BKSGE_NOEXCEPT
{
	return detail::llrint_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR long long
llrint(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::llrint_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LLRINT_HPP
