/**
 *	@file	erfc.hpp
 *
 *	@brief	erfc 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ERFC_HPP
#define BKSGE_FND_CMATH_ERFC_HPP

#include <bksge/fnd/cmath/detail/erfc_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	算術型の相補誤差関数 (complementary error function) を求める。
 *
 *	@param	arg	対象となる値
 *
 *	@return	引数 arg の相補誤差関数を返す。
 *
 *	arg が +∞  の場合、+0 を返す。
 *	arg が -∞  の場合、2  を返す。
 *	arg が NaN の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
erfc(float arg) BKSGE_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

inline BKSGE_CONSTEXPR float
erfcf(float arg) BKSGE_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

inline BKSGE_CONSTEXPR double
erfc(double arg) BKSGE_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

inline BKSGE_CONSTEXPR long double
erfc(long double arg) BKSGE_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

inline BKSGE_CONSTEXPR long double
erfcl(long double arg) BKSGE_NOEXCEPT
{
	return detail::erfc_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
erfc(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::erfc_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ERFC_HPP
