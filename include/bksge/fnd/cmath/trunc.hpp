/**
 *	@file	trunc.hpp
 *
 *	@brief	trunc 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_TRUNC_HPP
#define BKSGE_FND_CMATH_TRUNC_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ゼロ方向への丸め
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x をゼロ方向に丸めた整数値
 *
 *	ゼロ方向に丸めた整数値とは、絶対値が引数 x の絶対値以下で、かつ、引数 x に最も近い整数値である。
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0  の場合、xをそのまま返す。
 *	x が NaN  の場合、NaNを返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		bksge::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
trunc(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/trunc_inl.hpp>

#endif // BKSGE_FND_CMATH_TRUNC_HPP
