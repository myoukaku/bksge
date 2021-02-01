/**
 *	@file	hypot.hpp
 *
 *	@brief	hypot 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_HYPOT_HPP
#define BKSGE_FND_CMATH_HYPOT_HPP

#include <bksge/fnd/cmath/detail/hypot_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	平方和の平方根を求める
 *
 *	@param	x
 *	@param	y
 *
 *	@return	引数 x と引数 y の平方和の平方根を返す。この際、余計なオーバーフロー、アンダーフローを起こさない。
 *
 *	x が ±0の場合、fabs(y) を返す
 *	y が ±0の場合、fabs(x) を返す
 *	x と y のどちらか一方でも±∞の場合（もう一方が NaN であっても）、+∞を返す
 *	上記を満たさずに、x と y のどちらか一方でもNaNの場合、NaNを返す
 */
inline BKSGE_CONSTEXPR float
hypot(float x, float y) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

inline BKSGE_CONSTEXPR float
hypotf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

inline BKSGE_CONSTEXPR double
hypot(double x, double y) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
hypot(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
hypotl(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y);
}

/**
 *	@brief	平方和の平方根を求める(任意の算術型版)
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *
 *	@note	引数が整数型の場合、doubleにキャストされる
 *
 *	@note	引数にlong doubleが含まれる場合、戻り値の型はlong double
 *			そうでない場合、戻り値の型はdouble
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
hypot(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::hypot_impl(static_cast<type>(x), static_cast<type>(y));
}

/**
 *	@brief	平方和の平方根を求める(3引数版)
 *
 *	@param	x
 *	@param	y
 *	@param	z
 *
 *	@return	x, y, z の平方和の平方根を返す。この際、余計なオーバーフロー、アンダーフローを起こさない。
 *
 *	x と y が ±0の場合、fabs(z) を返す
 *	y と z が ±0の場合、fabs(x) を返す
 *	z と x が ±0の場合、fabs(y) を返す
 *	引数のどれか1個でも ±∞ の場合（他の引数が NaN であっても）、+∞を返す
 *	上記を満たさずに、引数のどれか1個でも NaN の場合、NaN を返す
 */
inline BKSGE_CONSTEXPR float
hypot(float x, float y, float z) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y, z);
}

inline BKSGE_CONSTEXPR double
hypot(double x, double y, double z) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y, z);
}

inline BKSGE_CONSTEXPR long double
hypot(long double x, long double y, long double z) BKSGE_NOEXCEPT
{
	return detail::hypot_impl(x, y, z);
}

/**
 *	@brief	平方和の平方根を求める(3引数、任意の算術型版)
 *
 *	@tparam	Arithmetic1	算術型
 *	@tparam	Arithmetic2	算術型
 *	@tparam	Arithmetic3	算術型
 */
template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic3)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
hypot(Arithmetic1 x, Arithmetic2 y, Arithmetic3 z) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::hypot_impl(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_HYPOT_HPP
