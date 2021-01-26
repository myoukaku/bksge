/**
 *	@file	acosh.hpp
 *
 *	@brief	acosh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ACOSH_HPP
#define BKSGE_FND_CMATH_ACOSH_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	逆双曲線余弦（アークハイパボリックコサイン）を求める
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの逆双曲線余弦を返す
 *
 *	x < 1  の場合、NaN を返す。
 *	x = 1  の場合、+0  を返す。
 *	x が +∞ の場合、+∞ を返す。
 *	x が NaN の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<bksge::is_arithmetic<ArithmeticType>::value>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
acosh(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/acosh_inl.hpp>

#endif // BKSGE_FND_CMATH_ACOSH_HPP
