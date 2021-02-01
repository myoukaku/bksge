/**
 *	@file	tanh.hpp
 *
 *	@brief	tanh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_TANH_HPP
#define BKSGE_FND_CMATH_TANH_HPP

#include <bksge/fnd/cmath/detail/tanh_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	双曲線正接（ハイパボリックタンジェント）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの正接を返す
 *
 *	arg が ±0  の場合、±0を返す。
 *	arg が ±∞ の場合、±1を返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
tanh(float arg) BKSGE_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

inline BKSGE_CONSTEXPR float
tanhf(float arg) BKSGE_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

inline BKSGE_CONSTEXPR double
tanh(double arg) BKSGE_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
tanh(long double arg) BKSGE_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
tanhl(long double arg) BKSGE_NOEXCEPT
{
	return detail::tanh_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
tanh(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::tanh_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_TANH_HPP
