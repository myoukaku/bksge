﻿/**
 *	@file	almost_equal.hpp
 *
 *	@brief	almost_equal 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ALMOST_EQUAL_HPP
#define BKSGE_FND_CMATH_ALMOST_EQUAL_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	2つの値がほぼ同じかどうかを調べる
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	xとyがほぼ同じ値ならtrue
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value
	>::type
>
BKSGE_CONSTEXPR bool
almost_equal(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::almost_equal;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/almost_equal_inl.hpp>

#endif // BKSGE_FND_CMATH_ALMOST_EQUAL_HPP
