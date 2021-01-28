/**
 *	@file	hypot.hpp
 *
 *	@brief	hypot 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_HYPOT_HPP
#define BKSGE_FND_CMATH_HYPOT_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	平方和の平方根を求める
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x と引数 y の平方和の平方根を返す。この際、余計なオーバーフロー、アンダーフローを起こさない。
 *
 *	x が ±0の場合、fabs(y) を返す
 *	y が ±0の場合、fabs(x) を返す
 *	x と y のどちらか一方でも±∞の場合（もう一方が NaN であっても）、+∞を返す
 *	上記を満たさずに、x と y のどちらか一方でもNaNの場合、NaNを返す
 */
BKSGE_CONSTEXPR float       hypot (float x, float y) BKSGE_NOEXCEPT;
BKSGE_CONSTEXPR float       hypotf(float x, float y) BKSGE_NOEXCEPT;
BKSGE_CONSTEXPR double      hypot (double x, double y) BKSGE_NOEXCEPT;
BKSGE_CONSTEXPR long double hypot (long double x, long double y) BKSGE_NOEXCEPT;
BKSGE_CONSTEXPR long double hypotl(long double x, long double y) BKSGE_NOEXCEPT;

/**
 *	@brief	平方和の平方根を求める(任意の算術型版)
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@note	引数が整数型の場合、doubleにキャストされる
 *
 *	@note	引数にlong doubleが含まれる場合、戻り値の型はlong double
 *			そうでない場合、戻り値の型はdouble
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType1>::value &&
		bksge::is_arithmetic<ArithmeticType2>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
hypot(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT;

/**
 *	@brief	平方和の平方根を求める(3引数版)
 *
 *	@param	x
 *	@param	y
 *	@param	z
 *
 *	@return	x, y, z の平方和の平方根を返す。この際、余計なオーバーフロー、アンダーフローを起こさない。
 *
 *	x と y が ±0の場合、fabs(z) を返す
 *	y と z が ±0の場合、fabs(x) を返す
 *	z と x が ±0の場合、fabs(y) を返す
 *	引数のどれか1個でも ±∞ の場合（他の引数が NaN であっても）、+∞を返す
 *	上記を満たさずに、引数のどれか1個でも NaN の場合、NaN を返す
 */
BKSGE_CONSTEXPR float       hypot (float x, float y, float z) BKSGE_NOEXCEPT;
BKSGE_CONSTEXPR double      hypot (double x, double y, double z) BKSGE_NOEXCEPT;
BKSGE_CONSTEXPR long double hypot (long double x, long double y, long double z) BKSGE_NOEXCEPT;

/**
 *	@brief	平方和の平方根を求める(3引数、任意の算術型版)
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *	@tparam	ArithmeticType3	算術型
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
hypot(ArithmeticType1 x, ArithmeticType2 y, ArithmeticType3 z) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/hypot_inl.hpp>

#endif // BKSGE_FND_CMATH_HYPOT_HPP
