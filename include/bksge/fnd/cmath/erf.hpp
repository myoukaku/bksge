/**
 *	@file	erf.hpp
 *
 *	@brief	erf 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ERF_HPP
#define BKSGE_FND_CMATH_ERF_HPP

#include <bksge/fnd/cmath/detail/erf_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	算術型の誤差関数 (error function) を求める。
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の誤差関数を返す。
 *
 *	arg が ±0  の場合、 ±0 を返す。
 *	arg が ±∞ の場合、  ±1 を返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
erf(float arg) BKSGE_NOEXCEPT
{
	return detail::erf_impl(arg);
}

inline BKSGE_CONSTEXPR float
erff(float arg) BKSGE_NOEXCEPT
{
	return detail::erf_impl(arg);
}

inline BKSGE_CONSTEXPR double
erf(double arg) BKSGE_NOEXCEPT
{
	return detail::erf_impl(arg);
}

inline BKSGE_CONSTEXPR long double
erf(long double arg) BKSGE_NOEXCEPT
{
	return detail::erf_impl(arg);
}

inline BKSGE_CONSTEXPR long double
erfl(long double arg) BKSGE_NOEXCEPT
{
	return detail::erf_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
erf(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::erf_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ERF_HPP
