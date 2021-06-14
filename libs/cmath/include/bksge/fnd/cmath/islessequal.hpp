/**
 *	@file	islessequal.hpp
 *
 *	@brief	islessequal 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISLESSEQUAL_HPP
#define BKSGE_FND_CMATH_ISLESSEQUAL_HPP

#include <bksge/fnd/cmath/detail/islessequal_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	xがyより小さいか、あるいは等しいかどうかを判定する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return x <= y
 *
 *	@note	islessequal(x, y)の値は、常に x <= y と等しい。
 *			ただし、islessequalはxとyが順序付けられていない場合に浮動小数点例外を生成しない。
 */
inline BKSGE_CONSTEXPR bool
islessequal(float x, float y) BKSGE_NOEXCEPT
{
	return detail::islessequal_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
islessequal(double x, double y) BKSGE_NOEXCEPT
{
	return detail::islessequal_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
islessequal(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::islessequal_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bool
islessequal(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::islessequal_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISLESSEQUAL_HPP
