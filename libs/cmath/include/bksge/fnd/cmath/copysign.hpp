/**
 *	@file	copysign.hpp
 *
 *	@brief	copysign 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_COPYSIGN_HPP
#define BKSGE_FND_CMATH_COPYSIGN_HPP

#include <bksge/fnd/cmath/detail/copysign_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	数の符号をコピーする
 *
 *	@param	x
 *	@param	y
 *
 *	@return	絶対値はxに等しく、符号はｙに等しい値を返す
 *
 *	※std::copysignとの違い
 *	yが±0または±NaNのとき、xの符号は変更されない。
 *	これはconstexpr関数にするための制限。
 */
inline BKSGE_CONSTEXPR float
copysign(float x, float y) BKSGE_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

inline BKSGE_CONSTEXPR float
copysignf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

inline BKSGE_CONSTEXPR double
copysign(double x, double y) BKSGE_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
copysign(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
copysignl(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::copysign_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
copysign(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::copysign_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_COPYSIGN_HPP
