/**
 *	@file	frexp.hpp
 *
 *	@brief	frexp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FREXP_HPP
#define BKSGE_FND_CMATH_FREXP_HPP

#include <bksge/fnd/cmath/detail/frexp_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	引数を正規化された仮数部と 2 の累乗へ分解する
 *
 *	@param	arg	算術型の値
 *
 *	frexp関数は引数argを仮数部と指数部に分解し、仮数部を戻り値で返し、指数を*expに書き込んで返す。
 *
 *	arg が ±0 の場合、 arg をそのまま返し、*expに0がセットされる
 *	arg が ±∞ の場合、 arg をそのまま返し、*expの値は不定
 *	arg が NaN の場合、NaN を返し、*expの値は不定
 */
inline BKSGE_CXX14_CONSTEXPR float
frexp(float arg, int* exp) BKSGE_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

inline BKSGE_CXX14_CONSTEXPR float
frexpf(float arg, int* exp) BKSGE_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

inline BKSGE_CXX14_CONSTEXPR double
frexp(double arg, int* exp) BKSGE_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

inline BKSGE_CXX14_CONSTEXPR long double
frexp(long double arg, int* exp) BKSGE_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

inline BKSGE_CXX14_CONSTEXPR long double
frexpl(long double arg, int* exp) BKSGE_NOEXCEPT
{
	return detail::frexp_impl(arg, exp);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CXX14_CONSTEXPR double
frexp(IntegralType arg, int* exp) BKSGE_NOEXCEPT
{
	return detail::frexp_impl(static_cast<double>(arg), exp);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FREXP_HPP
