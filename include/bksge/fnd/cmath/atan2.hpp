/**
 *	@file	atan2.hpp
 *
 *	@brief	atan2 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ATAN2_HPP
#define BKSGE_FND_CMATH_ATAN2_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	アークタンジェントを取得する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	y	算術型の値
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、y/xのアークタンジェントを返す
 *
 *	y が ±0  かつ、x が負の値または -0 の場合、±π を返す。
 *	y が ±0  かつ、x が正の値または +0 の場合、±0  を返す。
 *	y が ±∞ かつ、x が有限の値の場合、±π/2  を返す。
 *	y が ±∞ かつ、x が -∞ の場合、±3π/4  を返す。
 *	y が ±∞ かつ、x が +∞ の場合、±π/4 を返す。
 *	x が ±0  かつ、y が負の値の場合、-π/2 を返す。
 *	x が ±0  かつ、y が正の値の場合、+π/2 を返す。
 *	x が -∞  かつ、y が有限の正の値の場合、+π を返す。
 *	x が -∞  かつ、y が有限の負の値の場合、-π を返す。
 *	x が +∞  かつ、y が有限の正の値の場合、+0 を返す。
 *	x が +∞  かつ、y が有限の負の値の場合、-0 を返す。
 *	x か y の少なくともどちらかが NaN の場合、NaN を返す。
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
atan2(ArithmeticType1 y, ArithmeticType2 x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/atan2_inl.hpp>

#endif // BKSGE_FND_CMATH_ATAN2_HPP
