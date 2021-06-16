/**
 *	@file	isgreaterequal.hpp
 *
 *	@brief	isgreaterequal 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISGREATEREQUAL_HPP
#define BKSGE_FND_CMATH_ISGREATEREQUAL_HPP

#include <bksge/fnd/cmath/detail/isgreaterequal_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	xがyより大きいか、あるいは等しいかどうかを判定する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return x >= y
 *
 *	@note	isgreaterequal(x, y)の値は、常に x >= y と等しい。
 *			ただし、isgreaterequalはxとyが順序付けられていない場合に浮動小数点例外を生成しない。
 */
inline BKSGE_CONSTEXPR bool
isgreaterequal(float x, float y) BKSGE_NOEXCEPT
{
	return detail::isgreaterequal_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
isgreaterequal(double x, double y) BKSGE_NOEXCEPT
{
	return detail::isgreaterequal_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
isgreaterequal(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::isgreaterequal_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bool
isgreaterequal(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::isgreaterequal_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISGREATEREQUAL_HPP
