/**
 *	@file	lround.hpp
 *
 *	@brief	lround 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LROUND_HPP
#define BKSGE_FND_CMATH_LROUND_HPP

#include <bksge/fnd/cmath/detail/lround_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	四捨五入により丸めた整数値をlong型として得る。
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x を四捨五入により丸めた整数値を、long型の範囲に収めて返す。
 *
 *	ここで引数 x の四捨五入とは、x を最も近い整数に丸めるが、
 *	x の小数部分が 0.5 の場合には、x の符号が正負のいずれであってもゼロから遠い方向に丸めることを指す。
 *
 *	x が numeric_limits<long>::min() より小さい場合、numeric_limits<long>::min() を返す。
 *	x が numeric_limits<long>::max() より大きい場合、numeric_limits<long>::max() を返す。
 *	x が NaN の場合、numeric_limits<long>::min() を返す。
 */
inline BKSGE_CONSTEXPR long
lround(float arg) BKSGE_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline BKSGE_CONSTEXPR long
lroundf(float arg) BKSGE_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline BKSGE_CONSTEXPR long
lround(double arg) BKSGE_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline BKSGE_CONSTEXPR long
lround(long double arg) BKSGE_NOEXCEPT
{
	return detail::lround_impl(arg);
}

inline BKSGE_CONSTEXPR long
lroundl(long double arg) BKSGE_NOEXCEPT
{
	return detail::lround_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR long
lround(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::lround_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LROUND_HPP
