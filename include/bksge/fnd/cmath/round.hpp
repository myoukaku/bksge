/**
 *	@file	round.hpp
 *
 *	@brief	round 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ROUND_HPP
#define BKSGE_FND_CMATH_ROUND_HPP

#include <bksge/fnd/cmath/detail/round_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	四捨五入により丸めた整数値を得る。
 *
 *	@tparam	Arithmetic	算術型
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x を四捨五入により丸めた整数値
 *
 *	ここで引数 x の四捨五入とは、x を最も近い整数に丸めるが、
 *	x の小数部分が 0.5 の場合には、x の符号が正負のいずれであってもゼロから遠い方向に丸めることを指す。
 *
 *	x が ±∞ の場合、xをそのまま返す。
 *	x が ±0  の場合、xをそのまま返す。
 *	x が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
round(float arg) BKSGE_NOEXCEPT
{
	return detail::round_impl(arg);
}

inline BKSGE_CONSTEXPR float
roundf(float arg) BKSGE_NOEXCEPT
{
	return detail::round_impl(arg);
}

inline BKSGE_CONSTEXPR double
round(double arg) BKSGE_NOEXCEPT
{
	return detail::round_impl(arg);
}

inline BKSGE_CONSTEXPR long double
round(long double arg) BKSGE_NOEXCEPT
{
	return detail::round_impl(arg);
}

inline BKSGE_CONSTEXPR long double
roundl(long double arg) BKSGE_NOEXCEPT
{
	return detail::round_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
round(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::round_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ROUND_HPP
