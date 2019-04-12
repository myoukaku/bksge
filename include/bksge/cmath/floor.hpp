﻿/**
 *	@file	floor.hpp
 *
 *	@brief	floor 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_FLOOR_HPP
#define BKSGE_CMATH_FLOOR_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	床関数
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	x以下で最大の整数
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0  の場合、xをそのまま返す。
 *	x が NaN  の場合、NaNを返す。
 */
template <
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
floor(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::floor;

}	// namespace bksge

#include <bksge/cmath/inl/floor_inl.hpp>

#endif // BKSGE_CMATH_FLOOR_HPP