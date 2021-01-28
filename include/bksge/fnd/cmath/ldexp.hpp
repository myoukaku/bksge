/**
 *	@file	ldexp.hpp
 *
 *	@brief	ldexp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LDEXP_HPP
#define BKSGE_FND_CMATH_LDEXP_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	浮動小数点数に2の整数乗を掛ける
 *
 *	@tparam	ArithmeticType	算術型
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
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<bksge::is_arithmetic<ArithmeticType>::value>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
ldexp(ArithmeticType x, int exp) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/ldexp_inl.hpp>

#endif // BKSGE_FND_CMATH_LDEXP_HPP
