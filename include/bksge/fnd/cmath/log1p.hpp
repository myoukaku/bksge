/**
 *	@file	log1p.hpp
 *
 *	@brief	log1p 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOG1P_HPP
#define BKSGE_FND_CMATH_LOG1P_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	引数に 1 を足した値の、e (ネイピア数) を底とする自然対数を求める。
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x
 *
 *	@return	引数 x に対して 1+x の e (ネイピア数) を底とする自然対数を返す。
 *
 *	x が ±0    の場合、±0 を返す。
 *	x が -1     の場合、-∞ を返す。
 *	x が -1未満 の場合、NaN を返す。
 *	x が +∞    の場合、+∞ を返す。
 *	x が NaN    の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<bksge::is_arithmetic<ArithmeticType>::value>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
log1p(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/log1p_inl.hpp>

#endif // BKSGE_FND_CMATH_LOG1P_HPP
