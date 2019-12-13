/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SIGNBIT_HPP
#define BKSGE_FND_CMATH_SIGNBIT_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	負の値かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが負の値ならtrue,そうでないならfalse.
 *
 *	@note	ArithmeticTypeが整数型のときはdoubleにキャストしてから調べる。
 *
 *	※std::signbitとの違い
 *	xが±0または±NaNのとき、falseを返す。
 *	これはconstexpr関数にするための制限。
 */
template <
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bool
signbit(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::signbit;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/signbit_inl.hpp>

#endif // BKSGE_FND_CMATH_SIGNBIT_HPP
