/**
 *	@file	copysign.hpp
 *
 *	@brief	copysign 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COPYSIGN_HPP
#define BKSGE_FND_CMATH_COPYSIGN_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	数の符号をコピーする
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	絶対値はxに等しく、符号はｙに等しい値を返す
 *
 *	※std::copysignとの違い
 *	yが±0または±NaNのとき、xの符号は変更されない。
 *	これはconstexpr関数にするための制限。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
copysign(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::copysign;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/copysign_inl.hpp>

#endif // BKSGE_FND_CMATH_COPYSIGN_HPP
