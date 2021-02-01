/**
 *	@file	fdim.hpp
 *
 *	@brief	fdim 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FDIM_HPP
#define BKSGE_FND_CMATH_FDIM_HPP

#include <bksge/fnd/cmath/detail/fdim_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	正の差分を求める
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x と引数 y の正の差分を返す。
 *
 *	x > y の場合、x - y を返す。
 *	x <= y の場合、+0 を返す。
 *	x と y のどちらか一方でもNaNの場合、NaNを返す
 */
inline BKSGE_CONSTEXPR float
fdim(float x, float y) BKSGE_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

inline BKSGE_CONSTEXPR float
fdimf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

inline BKSGE_CONSTEXPR double
fdim(double x, double y) BKSGE_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
fdim(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
fdiml(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::fdim_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
fdim(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fdim_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FDIM_HPP
