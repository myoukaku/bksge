/**
 *	@file	acos.hpp
 *
 *	@brief	acos 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ACOS_HPP
#define BKSGE_FND_CMATH_ACOS_HPP

#include <bksge/fnd/cmath/detail/acos_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	アークコサインを取得する
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argのアークコサインを返す
 *
 *	arg が +1  の場合、+0  を返す。
 *	|arg| > 1  の場合、NaN を返す。
 *	arg が NaN の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
acos(float arg) BKSGE_NOEXCEPT
{
	return detail::acos_impl(arg);
}

inline BKSGE_CONSTEXPR float
acosf(float arg) BKSGE_NOEXCEPT
{
	return detail::acos_impl(arg);
}

inline BKSGE_CONSTEXPR double
acos(double arg) BKSGE_NOEXCEPT
{
	return detail::acos_impl(arg);
}

inline BKSGE_CONSTEXPR long double
acos(long double arg) BKSGE_NOEXCEPT
{
	return detail::acos_impl(arg);
}

inline BKSGE_CONSTEXPR long double
acosl(long double arg) BKSGE_NOEXCEPT
{
	return detail::acos_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
acos(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::acos_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ACOS_HPP
