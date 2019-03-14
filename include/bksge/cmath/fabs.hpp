/**
 *	@file	fabs.hpp
 *
 *	@brief	fabs 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_FABS_HPP
#define BKSGE_CMATH_FABS_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>
#include <type_traits>

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
 *	x が ±0  の場合、+0  を返す。
 *	x が ±∞ の場合、+∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
template <
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
fabs(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::fabs;

}	// namespace bksge

#include <bksge/cmath/inl/fabs_inl.hpp>

#endif // BKSGE_CMATH_FABS_HPP
