/**
 *	@file	remainder.hpp
 *
 *	@brief	remainder 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_REMAINDER_HPP
#define BKSGE_FND_CMATH_REMAINDER_HPP

#include <bksge/fnd/cmath/detail/remainder_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	剰余を求めます
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x / y の余り
 *
 *	remainder関数はxをyで割った余りを計算する。
 *	返り値は x - n * y である。
 *	ここで n は x / y の値を最も近い整数に丸めたものである。
 *	n - x / y の絶対値が0.5の場合、偶数になるようにnが選ばれる。
 *
 *	fmod関数と違い、戻り値の符号はxと同じになるとは限らない。
 *	ただし戻り値が0の場合、xと同じ符号になる。
 *
 *	x が ±∞ かつ、y が NaN でない場合、NaN を返す。
 *	y が ±0  かつ、x が NaN でない場合、NaN を返す。
 *	x か y がNaNの場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
remainder(float x, float y) BKSGE_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

inline BKSGE_CONSTEXPR float
remainderf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

inline BKSGE_CONSTEXPR double
remainder(double x, double y) BKSGE_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
remainder(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
remainderl(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::remainder_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
remainder(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::remainder_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_REMAINDER_HPP
