/**
 *	@file	atanh.hpp
 *
 *	@brief	atanh 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ATANH_HPP
#define BKSGE_FND_CMATH_ATANH_HPP

#include <bksge/fnd/cmath/detail/atanh_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	逆双曲線正接（アークハイパボリックタンジェント）を求める
 *
 *	@param	arg	算術型の値
 *
 *	@return	関数に成功すると、argの逆双曲線正接を返す
 *
 *	arg が ±0 の場合、argをそのまま返す。
 *	arg が ±1 の場合、±∞を返す。
 *	|arg| > 1  の場合、NaN を返す。
 *	arg が NaN の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
atanh(float arg) BKSGE_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

inline BKSGE_CONSTEXPR float
atanhf(float arg) BKSGE_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

inline BKSGE_CONSTEXPR double
atanh (double arg) BKSGE_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
atanh (long double arg) BKSGE_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

inline BKSGE_CONSTEXPR long double
atanhl(long double arg) BKSGE_NOEXCEPT
{
	return detail::atanh_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
atanh(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::atanh_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ATANH_HPP
