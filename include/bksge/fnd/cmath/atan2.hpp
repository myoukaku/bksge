/**
 *	@file	atan2.hpp
 *
 *	@brief	atan2 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ATAN2_HPP
#define BKSGE_FND_CMATH_ATAN2_HPP

#include <bksge/fnd/cmath/detail/atan2_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	アークタンジェントを取得する
 *
 *	@param	y	算術型の値
 *	@param	x	算術型の値
 *
 *	@return	関数に成功すると、y/xのアークタンジェントを返す
 *
 *	y が ±0  かつ、x が負の値または -0 の場合、±π を返す。
 *	y が ±0  かつ、x が正の値または +0 の場合、±0  を返す。
 *	y が ±∞ かつ、x が有限の値の場合、±π/2  を返す。
 *	y が ±∞ かつ、x が -∞ の場合、±3π/4  を返す。
 *	y が ±∞ かつ、x が +∞ の場合、±π/4 を返す。
 *	x が ±0  かつ、y が負の値の場合、-π/2 を返す。
 *	x が ±0  かつ、y が正の値の場合、+π/2 を返す。
 *	x が -∞  かつ、y が有限の正の値の場合、+π を返す。
 *	x が -∞  かつ、y が有限の負の値の場合、-π を返す。
 *	x が +∞  かつ、y が有限の正の値の場合、+0 を返す。
 *	x が +∞  かつ、y が有限の負の値の場合、-0 を返す。
 *	x か y の少なくともどちらかが NaN の場合、NaN を返す。
 */
inline BKSGE_CONSTEXPR float
atan2(float y, float x) BKSGE_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

inline BKSGE_CONSTEXPR float
atan2f(float y, float x) BKSGE_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

inline BKSGE_CONSTEXPR double
atan2(double y, double x) BKSGE_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

inline BKSGE_CONSTEXPR long double
atan2(long double y, long double x) BKSGE_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

inline BKSGE_CONSTEXPR long double
atan2l(long double y, long double x) BKSGE_NOEXCEPT
{
	return detail::atan2_impl(y, x);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
atan2(Arithmetic1 y, Arithmetic2 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::atan2_impl(static_cast<type>(y), static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ATAN2_HPP
