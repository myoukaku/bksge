/**
 *	@file	asin.hpp
 *
 *	@brief	asin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ASIN_HPP
#define BKSGE_FND_CMATH_ASIN_HPP

#include <bksge/fnd/cmath/detail/asin_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	アークサインを取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argのアークサインを返す
 *
 *	arg が ±0 の場合、arg をそのまま返す。
 *	|arg| > 1  の場合、NaN を返す。
 *	arg が NaN の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
asin(float arg) BKSGE_NOEXCEPT
{
	return detail::asin_impl(arg);
}

inline BKSGE_CONSTEXPR float
asinf(float arg) BKSGE_NOEXCEPT
{
	return detail::asin_impl(arg);
}

inline BKSGE_CONSTEXPR double
asin(double arg) BKSGE_NOEXCEPT
{
	return detail::asin_impl(arg);
}

inline BKSGE_CONSTEXPR long double
asin(long double arg) BKSGE_NOEXCEPT
{
	return detail::asin_impl(arg);
}

inline BKSGE_CONSTEXPR long double
asinl(long double arg) BKSGE_NOEXCEPT
{
	return detail::asin_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
asin(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::asin_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ASIN_HPP
