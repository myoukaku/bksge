/**
 *	@file	abs.hpp
 *
 *	@brief	abs 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ABS_HPP
#define BKSGE_FND_CMATH_ABS_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	絶対値を求める
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの絶対値を返す
 *
 *	bksge::fabs関数との違い：
 *	・戻り値の型が引数の型と同じ
 *
 *	・xが整数型(IntegralType)の場合
 *	　結果の値を戻り値の型の範囲で表せない場合、動作は未定義となる。
 *	　例えば2の補数を使う処理系において、
 *	　abs(INT_MIN)の結果はINT_MAXより大きいためint型で表すことができない。
 *
 *	・xが浮動小数点型(FloatingPointType)の場合
 *	　+0と-0を区別しない。
 *	　+NaNと-NaNを区別しない。
 *
 *	・上記のようなチェックをしていないぶん、fabs関数より高速になる可能性がある。
 *
 *	標準ライブラリ<cmath>のabs関数との違い:
 *	　<cmath>のabs関数はfabs関数と同じだが、bksge::absは違う。
 *
 *	標準ライブラリ<cstdlib>のabs関数との違い:
 *	　bksge::absは全ての算術型に対応している。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR ArithmeticType
abs(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::abs;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/abs_inl.hpp>

#endif // BKSGE_FND_CMATH_ABS_HPP
