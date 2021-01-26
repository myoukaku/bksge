/**
 *	@file	log.hpp
 *
 *	@brief	log 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LOG_HPP
#define BKSGE_FND_CMATH_LOG_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	e (ネイピア数) を底とする自然対数を求める
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x の e (ネイピア数) を底とする自然対数
 *
 *	x が ±0 だった場合、-∞ を返す。
 *	x が 1   だった場合、+0  を返す。
 *	x < 0    だった場合、NaN を返す。
 *	x が +∞ だった場合、+∞ を返す。
 *	x が NaN だった場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<bksge::is_arithmetic<ArithmeticType>::value>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
log(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/log_inl.hpp>

#endif // BKSGE_FND_CMATH_LOG_HPP
