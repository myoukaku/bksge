/**
 *	@file	ceil.hpp
 *
 *	@brief	ceil 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_CEIL_HPP
#define BKSGE_FND_CMATH_CEIL_HPP

#include <bksge/fnd/cmath/detail/ceil_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	天井関数
 *
 *	@param	arg	対象となる値
 *
 *	@return	arg以上で最小の整数
 *
 *	arg が ±∞ の場合、argをそのまま返す。
 *	arg が ±0  の場合、argをそのまま返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
ceil(float arg) BKSGE_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

inline BKSGE_CONSTEXPR float
ceilf(float arg) BKSGE_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

inline BKSGE_CONSTEXPR double
ceil(double arg) BKSGE_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

inline BKSGE_CONSTEXPR long double
ceil(long double arg) BKSGE_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

inline BKSGE_CONSTEXPR long double
ceill(long double arg) BKSGE_NOEXCEPT
{
	return detail::ceil_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
ceil(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::ceil_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_CEIL_HPP
