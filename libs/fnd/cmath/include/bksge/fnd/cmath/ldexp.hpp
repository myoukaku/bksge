/**
 *	@file	ldexp.hpp
 *
 *	@brief	ldexp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LDEXP_HPP
#define BKSGE_FND_CMATH_LDEXP_HPP

#include <bksge/fnd/cmath/detail/ldexp_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	浮動小数点数に2の整数乗を掛ける
 *
 *	@param	x	浮動小数点型の値
 *	@param	exp	整数型の値
 *
 *	@return	x に 2 の exp 乗を掛ける(x * (2 ^ exp))
 *
 *	x が ±0  だった場合、x をそのまま返す。
 *	x が ±∞ だった場合、x をそのまま返す。
 *	exp が 0 だった場合、x をそのまま返す。
 *	x が NaN だった場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
ldexp(float x, int exp) BKSGE_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

inline BKSGE_CONSTEXPR float
ldexpf(float x, int exp) BKSGE_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

inline BKSGE_CONSTEXPR double
ldexp(double x, int exp) BKSGE_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

inline BKSGE_CONSTEXPR long double
ldexp(long double x, int exp) BKSGE_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

inline BKSGE_CONSTEXPR long double
ldexpl(long double x, int exp) BKSGE_NOEXCEPT
{
	return detail::ldexp_impl(x, exp);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
ldexp(IntegralType x, int exp) BKSGE_NOEXCEPT
{
	return detail::ldexp_impl(static_cast<double>(x), exp);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LDEXP_HPP
