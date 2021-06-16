/**
 *	@file	modf.hpp
 *
 *	@brief	modf 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_MODF_HPP
#define BKSGE_FND_CMATH_MODF_HPP

#include <bksge/fnd/cmath/detail/modf_impl.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	引数を整数部と小数部に分割します
 *
 *	@param	x	算術型の値
 *
 *	@return	引数xの小数部を符号付きとして返す。また、引数xの整数部を*iptrに書き込む。
 *
 *	x が ±0  の場合、±0 を返し、*iptrに ±0 がセットされる。
 *	x が ±∞  の場合、±0 を返し、*iptrに ±∞ がセットされる。
 *	x が NaN の場合、NaN を返し、*iptrに NaN がセットされる。
 */
inline BKSGE_CONSTEXPR float
modf(float x, float* iptr) BKSGE_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

inline BKSGE_CONSTEXPR float
modff(float x, float* iptr) BKSGE_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

inline BKSGE_CONSTEXPR double
modf(double x, double* iptr) BKSGE_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

inline BKSGE_CONSTEXPR long double
modf(long double x, long double* iptr) BKSGE_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

inline BKSGE_CONSTEXPR long double
modfl(long double x, long double* iptr) BKSGE_NOEXCEPT
{
	return detail::modf_impl(x, iptr);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_MODF_HPP
