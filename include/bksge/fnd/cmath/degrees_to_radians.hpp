/**
 *	@file	degrees_to_radians.hpp
 *
 *	@brief	degrees_to_radians 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DEGREES_TO_RADIANS_HPP
#define BKSGE_FND_CMATH_DEGREES_TO_RADIANS_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	デグリー値をラジアン値に変換する
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	デグリー値
 *
 *	@return	関数に成功すると、xをラジアン値に変換した値を返す
 *
 *	x が ±∞ の場合、±∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
degrees_to_radians(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/degrees_to_radians_inl.hpp>

#endif // BKSGE_FND_CMATH_DEGREES_TO_RADIANS_HPP
