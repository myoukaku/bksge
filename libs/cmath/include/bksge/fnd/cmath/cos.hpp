/**
 *	@file	cos.hpp
 *
 *	@brief	cos 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COS_HPP
#define BKSGE_FND_CMATH_COS_HPP

#include <bksge/fnd/cmath/detail/cos_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	余弦（コサイン）を取得する
 *
 *	@param	arg	算術型の値(ラジアン）
 *
 *	@return	関数に成功すると、argのコサインを返す
 *
 *	arg が ±0  の場合、1を返す。
 *	arg が ±∞ の場合、NaNを返す。
 *	arg が NaN  の場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
cos(float arg) BKSGE_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline BKSGE_CONSTEXPR float
cosf(float arg) BKSGE_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline BKSGE_CONSTEXPR double
cos(double arg) BKSGE_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline BKSGE_CONSTEXPR long double
cos(long double arg) BKSGE_NOEXCEPT
{
	return detail::cos_impl(arg);
}

inline BKSGE_CONSTEXPR long double
cosl(long double arg) BKSGE_NOEXCEPT
{
	return detail::cos_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR double
cos(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::cos_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_COS_HPP
