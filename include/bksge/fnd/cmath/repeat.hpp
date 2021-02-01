/**
 *	@file	repeat.hpp
 *
 *	@brief	repeat 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_REPEAT_HPP
#define BKSGE_FND_CMATH_REPEAT_HPP

#include <bksge/fnd/cmath/detail/repeat_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		回り込み処理
 *
 *	@tparam		Arithmetic1
 *	@tparam		Arithmetic2
 *	@tparam		Arithmetic3
 *
 *	@param		x	対象となる値
 *	@param		min	最小値
 *	@param		max	最大値
 *
 *	@return		x を min 以上 max 未満の範囲で回り込み処理をした値
 *
 *	x, min, max のどれか1つでも NaN  の場合、NaN を返す。
 *	x, min, max のどれか1つでも ±∞ の場合、NaN を返す。
 *	min > max の場合、NaN を返す。
 *	min == max の場合、min を返す。
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic3)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
repeat(Arithmetic1 x, Arithmetic2 min, Arithmetic3 max) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;

	return detail::repeat_impl(
		static_cast<type>(x),
		static_cast<type>(min),
		static_cast<type>(max));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_REPEAT_HPP
