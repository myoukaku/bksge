/**
 *	@file	degrees_to_radians.hpp
 *
 *	@brief	degrees_to_radians 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DEGREES_TO_RADIANS_HPP
#define BKSGE_FND_CMATH_DEGREES_TO_RADIANS_HPP

#include <bksge/fnd/cmath/detail/degrees_to_radians_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	デグリー値をラジアン値に変換する
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	デグリー値
 *
 *	@return	関数に成功すると、xをラジアン値に変換した値を返す
 *
 *	x が ±∞ の場合、±∞ を返す。
 *	x が NaN  の場合、NaN を返す。
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic>
degrees_to_radians(Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::degrees_to_radians_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DEGREES_TO_RADIANS_HPP
