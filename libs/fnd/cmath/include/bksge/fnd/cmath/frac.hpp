﻿/**
 *	@file	frac.hpp
 *
 *	@brief	frac 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FRAC_HPP
#define BKSGE_FND_CMATH_FRAC_HPP

#include <bksge/fnd/cmath/detail/frac_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	小数部を求める
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、xの小数部（常に正）を返す
 *
 *	x が ±∞の場合、+0  を返す。
 *	x が NaN の場合、NaN を返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic>
frac(Arithmetic x) BKSGE_NOEXCEPT
{
	return detail::frac_impl(x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FRAC_HPP
