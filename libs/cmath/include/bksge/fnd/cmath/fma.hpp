/**
 *	@file	fma.hpp
 *
 *	@brief	fma 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FMA_HPP
#define BKSGE_FND_CMATH_FMA_HPP

#include <bksge/fnd/cmath/detail/fma_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	和積演算(FMA; fused multiply-add)
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *	@tparam	ArithmeticType3	算術型
 *
 *	@param	x	算術型の値
 *	@param	y	算術型の値
 *	@param	z	算術型の値
 *
 *	@return	関数に成功すると、(x * y) + z を返す。
 *			丸めは乗算と加算の後に1回だけ行われる。
 *
 *	xが±0でyが±∞の場合、NaNを返す。
 *	xが±∞でyが±0の場合、NaNを返す。
 *	x*y の結果が±∞になり、zがそれとは逆の符号の∞の場合、NaNを返す。
 *	xかyがNaNの場合、NaNを返す。
 *	zがNaNで、x*y が 0*inf または inf*0 でない場合、NaNを返す。
 */
inline BKSGE_CONSTEXPR float
fma(float x, float y, float z) BKSGE_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

inline BKSGE_CONSTEXPR float
fmaf(float x, float y, float z) BKSGE_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

inline BKSGE_CONSTEXPR double
fma(double x, double y, double z) BKSGE_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

inline BKSGE_CONSTEXPR long double
fma(long double x, long double y, long double z) BKSGE_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

inline BKSGE_CONSTEXPR long double
fmal(long double x, long double y, long double z) BKSGE_NOEXCEPT
{
	return detail::fma_impl(x, y, z);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic3)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>
fma(Arithmetic1 x, Arithmetic2 y, Arithmetic3 z) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2, Arithmetic3>;
	return detail::fma_impl(static_cast<type>(x), static_cast<type>(y), static_cast<type>(z));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FMA_HPP
