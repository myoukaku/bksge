/**
 *	@file	repeat.hpp
 *
 *	@brief	repeat 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_REPEAT_HPP
#define BKSGE_FND_CMATH_REPEAT_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		回り込み処理
 *
 *	@tparam		ArithmeticType1
 *	@tparam		ArithmeticType2
 *	@tparam		ArithmeticType3
 *
 *	@param		x	対象となる値
 *	@param		min	最小値
 *	@param		max	最大値
 *
 *	@return		x を min 以上 max 未満の範囲で回り込み処理をした値
 *
 *	x, min, max のどれか1つでも NaN  の場合、NaN を返す。
 *	x, min, max のどれか1つでも ±∞ の場合、NaN を返す。
 *	min > max の場合、NaN を返す。
 *	min == max の場合、min を返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename ArithmeticType3,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType1>::value &&
		bksge::is_arithmetic<ArithmeticType2>::value &&
		bksge::is_arithmetic<ArithmeticType3>::value
	>
>
BKSGE_CONSTEXPR
bksge::float_promote_t<
	ArithmeticType1,
	ArithmeticType2,
	ArithmeticType3
>
repeat(
	ArithmeticType1 x,
	ArithmeticType2 min,
	ArithmeticType3 max) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/repeat_inl.hpp>

#endif // BKSGE_FND_CMATH_REPEAT_HPP
