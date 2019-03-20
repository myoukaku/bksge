/**
 *	@file	round_down.hpp
 *
 *	@brief	round_down 関数の宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_ROUND_DOWN_HPP
#define BKSGE_CMATH_ROUND_DOWN_HPP

#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	切り下げ
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x		切り下げる数
 *	@param	base	基数
 *
 *	@return	xをbaseの倍数に切り下げた値
 *
 *	xをbaseの倍数に切り下げた値を取得します。
 *	正確に言うと
 *	a % base = 0 (a <= x) となる最大の整数aを取得します。
 *
 *	base が NaN  の場合、NaN  を返す。
 *	x が NaN     の場合、NaN  を返す。
 *	base が ±∞ の場合、±∞ を返す。
 *	x が ±∞    の場合、±∞ を返す。
 *	base == 0　  の場合、x    を返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value
	>::type
>
BKSGE_CONSTEXPR ArithmeticType1
round_down(ArithmeticType1 x, ArithmeticType2 base) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::round_down;

}	// namespace bksge

#include <bksge/cmath/inl/round_down_inl.hpp>

#endif // BKSGE_CMATH_ROUND_DOWN_HPP
