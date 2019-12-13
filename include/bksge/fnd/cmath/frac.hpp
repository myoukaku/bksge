/**
 *	@file	frac.hpp
 *
 *	@brief	frac 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FRAC_HPP
#define BKSGE_FND_CMATH_FRAC_HPP

#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	小数部を求める
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの小数部（常に正）を返す
 *
 *	x が ±∞の場合、+0  を返す。
 *	x が NaN の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
frac(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::frac;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/frac_inl.hpp>

#endif // BKSGE_FND_CMATH_FRAC_HPP
