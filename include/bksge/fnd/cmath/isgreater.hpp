/**
 *	@file	isgreater.hpp
 *
 *	@brief	isgreater 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISGREATER_HPP
#define BKSGE_FND_CMATH_ISGREATER_HPP

#include <bksge/fnd/cmath/detail/isgreater_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	xがyより大きいかどうかを判定する
 *
 *	@param	x
 *	@param	y
 *
 *	@return x > y
 *
 *	@note	isgreater(x, y)の値は、常に x > y と等しい。
 *			ただし、isgreaterはxとyが順序付けられていない場合に浮動小数点例外を生成しない。
 */
inline BKSGE_CONSTEXPR bool
isgreater(float x, float y) BKSGE_NOEXCEPT
{
	return detail::isgreater_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
isgreater(double x, double y) BKSGE_NOEXCEPT
{
	return detail::isgreater_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
isgreater(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::isgreater_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bool
isgreater(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::isgreater_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISGREATER_HPP
