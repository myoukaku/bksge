/**
 *	@file	fabs.hpp
 *
 *	@brief	fabs 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FABS_HPP
#define BKSGE_FND_CMATH_FABS_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
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
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
fabs(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::fabs;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/fabs_inl.hpp>

#endif // BKSGE_FND_CMATH_FABS_HPP
