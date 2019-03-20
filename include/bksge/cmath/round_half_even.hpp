/**
 *	@file	round_half_even.hpp
 *
 *	@brief	round_half_even 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_ROUND_HALF_EVEN_HPP
#define BKSGE_CMATH_ROUND_HALF_EVEN_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	最近接偶数への丸め
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	xを最近接偶数へ丸めた値
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0  の場合、xをそのまま返す。
 *	x が NaN  の場合、NaNを返す。
 *
 *	@note	端数が0.5より小さいなら切り捨て、
 *			端数が0.5より大きいならは切り上げ、
 *			端数がちょうど0.5なら切り捨てと切り上げのうち結果が偶数となる方へ丸める。
 *			多数のデータを丸めた値を足しあわせても、丸め誤差が特定の側に偏って累積しない。
 *			「偶数丸め」「最近接丸め」「JIS丸め」「ISO丸め」「銀行家の丸め」「銀行丸め」
 *			「五捨五入」「偶捨奇入」と呼ばれたりもする。
 *
 *	https://ja.wikipedia.org/wiki/%E7%AB%AF%E6%95%B0%E5%87%A6%E7%90%86#.E6.9C.80.E8.BF.91.E6.8E.A5.E5.81.B6.E6.95.B0.E3.81.B8.E3.81.AE.E4.B8.B8.E3.82.81
 */
template <
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
round_half_even(ArithmeticType x);

}	// namespace cmath

using cmath::round_half_even;

}	// namespace bksge

#include <bksge/cmath/inl/round_half_even_inl.hpp>

#endif // BKSGE_CMATH_ROUND_HALF_EVEN_HPP
