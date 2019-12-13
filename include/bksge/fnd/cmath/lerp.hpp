/**
 *	@file	lerp.hpp
 *
 *	@brief	lerp 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LERP_HPP
#define BKSGE_FND_CMATH_LERP_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	２つの値の間を線形補間します
 *
 *	@tparam		ArithmeticType1	算術型
 *	@tparam		ArithmeticType2	算術型
 *	@tparam		ArithmeticType3	算術型
 *
 *	@param	from	1つ目の値
 *	@param	to		2つ目の値
 *	@param	t		補間係数
 *	@return	２つの値を線形補間した値
 *
 *	戻り値は[from,to]の範囲にクランプはされない。
 *	from > to になっても問題ない。
 *
 *	・from, to, t のうちどれか1つでもNaNの場合、NaNを返す。
 *	・from か to が ±∞ の場合、NaNを返す。
 *	・t が ±∞ の場合、±∞を返す。
 *	・from == to の場合、fromを返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename ArithmeticType3,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value &&
		std::is_arithmetic<ArithmeticType3>::value
	>
>
BKSGE_CONSTEXPR
bksge::float_promote_t<
	ArithmeticType1,
	ArithmeticType2,
	ArithmeticType3
>
lerp(
	ArithmeticType1 from,
	ArithmeticType2 to,
	ArithmeticType3 t) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::lerp;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/lerp_inl.hpp>

#endif // BKSGE_FND_CMATH_LERP_HPP
