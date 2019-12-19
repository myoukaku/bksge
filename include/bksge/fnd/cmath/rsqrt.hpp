/**
 *	@file	rsqrt.hpp
 *
 *	@brief	rsqrt 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_RSQRT_HPP
#define BKSGE_FND_CMATH_RSQRT_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	平方根の逆数を取得する
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの平方根の逆数を返す
 *
 *	x が 0 よりも小さい場合、NaN を返す。
 *	x が +∞ の場合、+0   を返す。
 *	x が ±0 の場合、±∞ を返す。
 *	x が NaN の場合、NaN  を返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<
		std::is_arithmetic<ArithmeticType>::value
	>
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
rsqrt(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::rsqrt;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/rsqrt_inl.hpp>

#endif // BKSGE_FND_CMATH_RSQRT_HPP
