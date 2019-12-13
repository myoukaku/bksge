/**
 *	@file	round_up.hpp
 *
 *	@brief	round_up 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ROUND_UP_HPP
#define BKSGE_FND_CMATH_ROUND_UP_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	切り上げ
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x		切り上げる数
 *	@param	base	基数
 *
 *	@return	xをbaseの倍数に切り上げた値
 *
 *	xをbaseの倍数に切り上げた値を取得します。
 *	正確に言うと
 *	a % base = 0 (a >= x) となる最小の整数aを取得します。
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
round_up(ArithmeticType1 x, ArithmeticType2 base) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::round_up;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/round_up_inl.hpp>

#endif // BKSGE_FND_CMATH_ROUND_UP_HPP
