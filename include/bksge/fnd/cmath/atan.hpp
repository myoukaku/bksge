/**
 *	@file	atan.hpp
 *
 *	@brief	atan 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ATAN_HPP
#define BKSGE_FND_CMATH_ATAN_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	アークタンジェントを取得する
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xのアークタンジェントを返す
 *
 *	x が ±0 の場合、xをそのまま返す。
 *	x が +∞ の場合、+π/2 を返す。
 *	x が -∞ の場合、-π/2 を返す。
 *	x が NaN の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<bksge::is_arithmetic<ArithmeticType>::value>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
atan(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/atan_inl.hpp>

#endif // BKSGE_FND_CMATH_ATAN_HPP
