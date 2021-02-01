/**
 *	@file	round_down.hpp
 *
 *	@brief	round_down 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ROUND_DOWN_HPP
#define BKSGE_FND_CMATH_ROUND_DOWN_HPP

#include <bksge/fnd/cmath/detail/round_down_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	切り下げ
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@param	x		切り下げる数
 *	@param	base	基数
 *
 *	@return	xをbaseの倍数に切り下げた値
 *
 *	xをbaseの倍数に切り下げた値を取得します。
 *	正確に言うと
 *	a % base = 0 (a <= x) となる最大の整数aを取得します。
 *
 *	base が NaN  の場合、NaN  を返す。
 *	x が NaN     の場合、NaN  を返す。
 *	base が ±∞ の場合、±∞ を返す。
 *	x が ±∞    の場合、±∞ を返す。
 *	base == 0　  の場合、x    を返す。
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR Arithmetic1
round_down(Arithmetic1 x, Arithmetic2 base) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return static_cast<Arithmetic1>(
		detail::round_down_impl(static_cast<type>(x), static_cast<type>(base)));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ROUND_DOWN_HPP
