﻿/**
 *	@file	saturate.hpp
 *
 *	@brief	saturate 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_SATURATE_HPP
#define BKSGE_CMATH_SATURATE_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	値を0以上1以下の範囲に丸めます
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param x	対象となる値
 *
 *	@return	x < 0なら0, x > 1なら1, さもなくばx
 *
 *	x が NaN の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
saturate(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::saturate;

}	// namespace bksge

#include <bksge/cmath/inl/saturate_inl.hpp>

#endif // BKSGE_CMATH_SATURATE_HPP
