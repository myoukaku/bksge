/**
 *	@file	factorial.hpp
 *
 *	@brief	factorial 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FACTORIAL_HPP
#define BKSGE_FND_CMATH_FACTORIAL_HPP

#include <bksge/fnd/cmath/detail/factorial_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	階乗を計算する
 *
 *	n の階乗 n! は、1 から n までのすべての整数の積である。
 *	n = 0 のときは 1 と定義する。
 *
 *	結果の値がオーバーフローする場合、戻り値の型が
 *	・浮動小数点数型なら inf
 *	・整数型なら 0
 *	を返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR Arithmetic
factorial(unsigned int n) BKSGE_NOEXCEPT
{
	return detail::factorial_impl<Arithmetic>(n);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FACTORIAL_HPP
