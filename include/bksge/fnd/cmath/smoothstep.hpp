/**
 *	@file	smoothstep.hpp
 *
 *	@brief	smoothstep 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SMOOTHSTEP_HPP
#define BKSGE_FND_CMATH_SMOOTHSTEP_HPP

#include <bksge/fnd/cmath/detail/smoothstep_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	smoothstep
 *
 *	@tparam		Arithmetic1	算術型
 *	@tparam		Arithmetic2	算術型
 *	@tparam		Arithmetic3	算術型
 *
 *	@param	from	xの最小値
 *	@param	to		xの最大値
 *	@param	x		補間対象の値
 *
 *	@return	fromとtoの間をエルミート補間した値を返す。
 *
 *	from, to, x のうち少なくとも1つがNaNの場合、NaNを返す。
 *	from > to の場合、NaNを返す。
 *	x >= to の場合、1を返す。
 *	x <= from の場合、0を返す。
 *	from = to の場合、1を返す。
 *	fromとtoの両方が±∞の場合、NaNを返す。
 *	fromが±∞の場合、1を返す。
 *	toが±∞の場合、0を返す。
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic3)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
smoothstep(Arithmetic1 from, Arithmetic2 to, Arithmetic3 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::smoothstep_impl(static_cast<type>(from), static_cast<type>(to), static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SMOOTHSTEP_HPP
