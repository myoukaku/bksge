/**
 *	@file	remquo.hpp
 *
 *	@brief	remquo 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_REMQUO_HPP
#define BKSGE_FND_CMATH_REMQUO_HPP

#include <bksge/fnd/cmath/detail/remquo_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	商と剰余を求める
 *
 *	@param		x
 *	@param		y
 *	@param		quo
 *
 *	@return		remainder(x, y) と同じ値
 *
 *	*quo にセットされる値は、 x / y と同じ符号を持ち、x / y の整数の商の絶対値と
 *	2^Nを法として合同である絶対値を持つ値(N は 3以上の処理系定義の整数)
 *
 *	x が ±∞ かつ、y が NaN でない場合、NaN を返し、quoが指す値は未規定となる。
 *	y が ±0 かつ、x が NaN でない場合、NaN を返し、quoが指す値は未規定となる。
 *	x か y が NaN の場合、NaN を返し、quoが指す値は未規定となる。
 */
inline BKSGE_CONSTEXPR float
remquo(float x, float y, int* quo) BKSGE_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

inline BKSGE_CONSTEXPR float
remquof(float x, float y, int* quo) BKSGE_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

inline BKSGE_CONSTEXPR double
remquo(double x, double y, int* quo) BKSGE_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

inline BKSGE_CONSTEXPR long double
remquo(long double x, long double y, int* quo) BKSGE_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

inline BKSGE_CONSTEXPR long double
remquol(long double x, long double y, int* quo) BKSGE_NOEXCEPT
{
	return detail::remquo_impl(x, y, quo);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
remquo(Arithmetic1 x, Arithmetic2 y, int* quo) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::remquo_impl(static_cast<type>(x), static_cast<type>(y), quo);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_REMQUO_HPP
