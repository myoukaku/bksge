/**
 *	@file	is_negative.hpp
 *
 *	@brief	is_negative 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_IS_NEGATIVE_HPP
#define BKSGE_FND_CMATH_IS_NEGATIVE_HPP

#include <bksge/fnd/cmath/detail/is_negative_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	負の値かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	x < 0 ならtrue,そうでないならならfalse.
 *
 *	x が 0   の場合、falseを返す。
 *	x が NaN の場合、falseを返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR bool
is_negative(Arithmetic x) BKSGE_NOEXCEPT
{
	return detail::is_negative_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_IS_NEGATIVE_HPP
