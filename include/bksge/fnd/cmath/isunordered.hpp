/**
 *	@file	isunordered.hpp
 *
 *	@brief	isunordered 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISUNORDERED_HPP
#define BKSGE_FND_CMATH_ISUNORDERED_HPP

#include <bksge/fnd/cmath/detail/isunordered_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	引数が unordered かどうか判定する
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return x と y が unordered なら true
 *
 *	x と y が unordered かどうか、つまり x と y の少なくとも一方が NaN かどうか を判定する。
 */
inline BKSGE_CONSTEXPR bool
isunordered(float x, float y) BKSGE_NOEXCEPT
{
	return detail::isunordered_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
isunordered(double x, double y) BKSGE_NOEXCEPT
{
	return detail::isunordered_impl(x, y);
}

inline BKSGE_CONSTEXPR bool
isunordered(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::isunordered_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bool
isunordered(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::isunordered_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISUNORDERED_HPP
