/**
 *	@file	pow.hpp
 *
 *	@brief	pow 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_POW_HPP
#define BKSGE_FND_CMATH_POW_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	x の y 乗を求める。
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x を y 乗した値を返す。
 *
 *	x が ±0 かつ、y が0より小さい奇数の場合、±∞ を返す。
 *	x が ±0 かつ、y が0より小さい有限の値で偶数または非整数の場合、+∞ を返す。
 *	x が ±0 かつ、y が -∞ の場合、+∞ を返す。
 *	x が ±0 かつ、y が0より大きい奇数の場合、±0 を返す。
 *	x が ±0 かつ、y が0より大きい偶数または非整数の場合、+0 を返す。
 *	x が -1  かつ、y が ±∞ の場合、1 を返す。
 *	x が +1  の場合、1 を返す。
 *	y が ±0 の場合、1 を返す。
 *	x が0より小さい有限の値かつ、yが有限で非整数の場合、NaNを返す。
 *	|x| < 1 かつ、y が -∞ の場合、+∞ を返す。
 *	|x| > 1 かつ、y が -∞ の場合、+0 を返す。
 *	|x| < 1 かつ、y が +∞ の場合、+0 を返す。
 *	|x| > 1 かつ、y が +∞ の場合、+∞ を返す。
 *	x が -∞ かつ、y が負の奇数の場合、            -0 を返す。
 *	x が -∞ かつ、y が負の偶数または非整数の場合、+0 を返す。
 *	x が -∞ かつ、y が正の奇数の場合、            -∞ を返す。
 *	x が -∞ かつ、y が正の偶数または非整数の場合、+∞ を返す。
 *	x が +∞ かつ、y が負の値の場合、+0  を返す。
 *	x が +∞ かつ、y が正の値の場合、+∞ を返す。
 *	上記以外で、xかyの少なくともどちらかがNaNの場合、NaNを返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType1>::value &&
		bksge::is_arithmetic<ArithmeticType2>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
pow(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/pow_inl.hpp>

#endif // BKSGE_FND_CMATH_POW_HPP
