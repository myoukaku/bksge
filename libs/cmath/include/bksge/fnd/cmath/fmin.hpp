/**
 *	@file	fmin.hpp
 *
 *	@brief	fmin 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FMIN_HPP
#define BKSGE_FND_CMATH_FMIN_HPP

#include <bksge/fnd/cmath/detail/fmin_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	x と y のうち小さい方の値を返す
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x	算術型の値
 *	@param	y	算術型の値
 *
 *	@return	関数に成功すると、x と y のうち小さい方の値を返す
 *
 *	x が NaN の場合、y を返す。
 *	y が NaN の場合、x を返す。
 */
inline BKSGE_CONSTEXPR float
fmin(float x, float y) BKSGE_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

inline BKSGE_CONSTEXPR float
fminf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

inline BKSGE_CONSTEXPR double
fmin(double x, double y) BKSGE_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
fmin(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
fminl(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::fmin_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
fmin(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmin_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FMIN_HPP
