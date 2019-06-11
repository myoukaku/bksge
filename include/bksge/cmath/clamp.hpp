/**
 *	@file	clamp.hpp
 *
 *	@brief	clamp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_CLAMP_HPP
#define BKSGE_CMATH_CLAMP_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	値をmin以上max以下の範囲に丸めます
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *	@tparam	ArithmeticType3	算術型
 *
 *	@param x	対象となる値
 *	@param min	最小値
 *	@param max	最大値
 *
 *	@return	x < minならmin, x > maxならmax, さもなくばx
 *
 *	min > max の場合、NaN を返す。
 *	x, min, max のどれか1つでも NaN の場合、NaN を返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename ArithmeticType3,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value &&
		std::is_arithmetic<ArithmeticType3>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2, ArithmeticType3>
clamp(
	ArithmeticType1 x,
	ArithmeticType2 min,
	ArithmeticType3 max) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::clamp;

}	// namespace bksge

#include <bksge/cmath/inl/clamp_inl.hpp>

#endif // BKSGE_CMATH_CLAMP_HPP
