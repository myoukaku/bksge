/**
 *	@file	is_even.hpp
 *
 *	@brief	is_even 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_IS_EVEN_HPP
#define BKSGE_FND_CMATH_IS_EVEN_HPP

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	偶数かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが偶数ならtrue,そうでないならならfalse.
 *
 *	x が NaN または ±∞ の場合、falseを返す。
 */
template <
	typename ArithmeticType,
	typename = bksge::enable_if_t<bksge::is_arithmetic<ArithmeticType>::value>
>
BKSGE_CONSTEXPR bool
is_even(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/is_even_inl.hpp>

#endif // BKSGE_FND_CMATH_IS_EVEN_HPP
