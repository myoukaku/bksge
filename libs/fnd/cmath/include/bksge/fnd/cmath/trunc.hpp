/**
 *	@file	trunc.hpp
 *
 *	@brief	trunc 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_TRUNC_HPP
#define BKSGE_FND_CMATH_TRUNC_HPP

#include <bksge/fnd/cmath/detail/trunc_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	ゼロ方向への丸め
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg をゼロ方向に丸めた整数値
 *
 *	ゼロ方向に丸めた整数値とは、絶対値が引数 arg の絶対値以下で、かつ、引数 arg に最も近い整数値である。
 *
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
trunc(float arg) BKSGE_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline BKSGE_CONSTEXPR float
truncf(float arg) BKSGE_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline BKSGE_CONSTEXPR double
trunc(double arg) BKSGE_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline BKSGE_CONSTEXPR long double
trunc(long double arg) BKSGE_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

inline BKSGE_CONSTEXPR long double
truncl(long double arg) BKSGE_NOEXCEPT
{
	return detail::trunc_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
trunc(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::trunc_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_TRUNC_HPP
