/**
 *	@file	smoothstep.hpp
 *
 *	@brief	smoothstep 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SMOOTHSTEP_HPP
#define BKSGE_FND_CMATH_SMOOTHSTEP_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	smoothstep
 *
 *	@tparam		ArithmeticType1	算術型
 *	@tparam		ArithmeticType2	算術型
 *	@tparam		ArithmeticType3	算術型
 *
 *	@param	from	xの最小値
 *	@param	to		xの最大値
 *	@param	x		補間対象の値
 *
 *	@return	fromとtoの間をエルミート補間した値を返す。
 *
 *	from, to, x のうち少なくとも1つがNaNの場合、NaNを返す。
 *	from > to の場合、NaNを返す。
 *	x >= to の場合、1を返す。
 *	x <= from の場合、0を返す。
 *	from = to の場合、1を返す。
 *	fromとtoの両方が±∞の場合、NaNを返す。
 *	fromが±∞の場合、1を返す。
 *	toが±∞の場合、0を返す。
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
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2, ArithmeticType3>
smoothstep(ArithmeticType1 from, ArithmeticType2 to, ArithmeticType3 x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/smoothstep_inl.hpp>

#endif // BKSGE_FND_CMATH_SMOOTHSTEP_HPP
