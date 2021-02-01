/**
 *	@file	is_odd.hpp
 *
 *	@brief	is_odd 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_IS_ODD_HPP
#define BKSGE_FND_CMATH_IS_ODD_HPP

#include <bksge/fnd/cmath/detail/is_odd_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	奇数かどうか調べる
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが奇数ならtrue,そうでないならならfalse.
 *
 *	x が NaN または ±∞ の場合、falseを返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR bool
is_odd(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::is_odd_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_IS_ODD_HPP
