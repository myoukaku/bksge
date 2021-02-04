/**
 *	@file	double_factorial.hpp
 *
 *	@brief	double_factorial 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DOUBLE_FACTORIAL_HPP
#define BKSGE_FND_CMATH_DOUBLE_FACTORIAL_HPP

#include <bksge/fnd/cmath/detail/double_factorial_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	二重階乗を計算する
 *
 *	二重階乗 n!! は、与えられた自然数 n に対し、
 *	1 から n まで n と同じ偶奇性を持つものだけを全て掛けた積を言う。
 *	n = 0 のときは 1 と定義する。
 *
 *	結果の値がオーバーフローする場合、戻り値の型が
 *	・浮動小数点数型なら inf
 *	・整数型なら 0
 *	を返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR Arithmetic
double_factorial(unsigned int n) BKSGE_NOEXCEPT
{
	return detail::double_factorial_impl<Arithmetic>(n);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DOUBLE_FACTORIAL_HPP
