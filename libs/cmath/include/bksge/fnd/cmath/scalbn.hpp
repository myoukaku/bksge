/**
 *	@file	scalbn.hpp
 *
 *	@brief	scalbn 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SCALBN_HPP
#define BKSGE_FND_CMATH_SCALBN_HPP

#include <bksge/fnd/cmath/detail/scalbn_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	浮動小数点数に基数の整数乗を掛ける
 *
 *	@param	x	浮動小数点型の値
 *	@param	exp	整数型の値
 *
 *	@return	x に FLT_RADIX の exp 乗を掛ける(x * (FLT_RADIX ^ exp))
 *
 *	x が ±0  だった場合、x をそのまま返す。
 *	x が ±∞  だった場合、x をそのまま返す。
 *	exp が 0 だった場合、x をそのまま返す。
 *	x が NaN だった場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
scalbn(float x, int exp) BKSGE_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

inline BKSGE_CONSTEXPR float
scalbnf(float x, int exp) BKSGE_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

inline BKSGE_CONSTEXPR double
scalbn(double x, int exp) BKSGE_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

inline BKSGE_CONSTEXPR long double
scalbn(long double x, int exp) BKSGE_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

inline BKSGE_CONSTEXPR long double
scalbnl(long double x, int exp) BKSGE_NOEXCEPT
{
	return detail::scalbn_impl(x, exp);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
scalbn(IntegralType x, int exp) BKSGE_NOEXCEPT
{
	return detail::scalbn_impl(static_cast<double>(x), exp);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SCALBN_HPP
