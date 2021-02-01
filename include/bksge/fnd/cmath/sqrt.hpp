/**
 *	@file	sqrt.hpp
 *
 *	@brief	sqrt 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SQRT_HPP
#define BKSGE_FND_CMATH_SQRT_HPP

#include <bksge/fnd/cmath/detail/sqrt_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	平方根を取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの平方根を返す
 *
 *	arg が 0 よりも小さい場合、NaNを返す。
 *	arg が +∞ の場合、argをそのまま返す。
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が NaN の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
sqrt(float arg) BKSGE_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

inline BKSGE_CONSTEXPR float
sqrtf(float arg) BKSGE_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

inline BKSGE_CONSTEXPR double
sqrt(double arg) BKSGE_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

inline BKSGE_CONSTEXPR long double
sqrt(long double arg) BKSGE_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

inline BKSGE_CONSTEXPR long double
sqrtl(long double arg) BKSGE_NOEXCEPT
{
	return detail::sqrt_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
sqrt(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::sqrt_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SQRT_HPP
