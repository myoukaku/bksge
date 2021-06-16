/**
 *	@file	pow.hpp
 *
 *	@brief	pow 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_POW_HPP
#define BKSGE_FND_CMATH_POW_HPP

#include <bksge/fnd/cmath/detail/pow_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	x の y 乗を求める。
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x を y 乗した値を返す。
 *
 *	x が ±0 かつ、y が0より小さい奇数の場合、±∞ を返す。
 *	x が ±0 かつ、y が0より小さい有限の値で偶数または非整数の場合、+∞ を返す。
 *	x が ±0 かつ、y が -∞ の場合、+∞ を返す。
 *	x が ±0 かつ、y が0より大きい奇数の場合、±0 を返す。
 *	x が ±0 かつ、y が0より大きい偶数または非整数の場合、+0 を返す。
 *	x が -1  かつ、y が ±∞ の場合、1 を返す。
 *	x が +1  の場合、1 を返す。
 *	y が ±0 の場合、1 を返す。
 *	x が0より小さい有限の値かつ、yが有限で非整数の場合、NaNを返す。
 *	|x| < 1 かつ、y が -∞ の場合、+∞ を返す。
 *	|x| > 1 かつ、y が -∞ の場合、+0 を返す。
 *	|x| < 1 かつ、y が +∞ の場合、+0 を返す。
 *	|x| > 1 かつ、y が +∞ の場合、+∞ を返す。
 *	x が -∞ かつ、y が負の奇数の場合、            -0 を返す。
 *	x が -∞ かつ、y が負の偶数または非整数の場合、+0 を返す。
 *	x が -∞ かつ、y が正の奇数の場合、            -∞ を返す。
 *	x が -∞ かつ、y が正の偶数または非整数の場合、+∞ を返す。
 *	x が +∞ かつ、y が負の値の場合、+0  を返す。
 *	x が +∞ かつ、y が正の値の場合、+∞ を返す。
 *	上記以外で、xかyの少なくともどちらかがNaNの場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
pow(float x, float y) BKSGE_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline BKSGE_CONSTEXPR float
powf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline BKSGE_CONSTEXPR double
pow(double x, double y) BKSGE_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
pow(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
powl(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::pow_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
pow(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::pow_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_POW_HPP
