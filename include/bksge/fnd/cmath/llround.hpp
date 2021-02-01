/**
 *	@file	llround.hpp
 *
 *	@brief	llround 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_LLROUND_HPP
#define BKSGE_FND_CMATH_LLROUND_HPP

#include <bksge/fnd/cmath/detail/llround_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	四捨五入により丸めた整数値をlong long型として得る。
 *
 *	@param	x	対象となる値
 *
 *	@return	引数 x を四捨五入により丸めた整数値を、long long型の範囲に収めて返す。
 *
 *	ここで引数 x の四捨五入とは、x を最も近い整数に丸めるが、
 *	x の小数部分が 0.5 の場合には、x の符号が正負のいずれであってもゼロから遠い方向に丸めることを指す。
 *
 *	x が numeric_limits<long long>::min() より小さい場合、numeric_limits<long long>::min() を返す。
 *	x が numeric_limits<long long>::max() より大きい場合、numeric_limits<long long>::max() を返す。
 *	x が NaN の場合、numeric_limits<long long>::min() を返す。
 */
inline BKSGE_CONSTEXPR long long
llround(float arg) BKSGE_NOEXCEPT
{
	return detail::llround_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llroundf(float arg) BKSGE_NOEXCEPT
{
	return detail::llround_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llround(double arg) BKSGE_NOEXCEPT
{
	return detail::llround_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llround(long double arg) BKSGE_NOEXCEPT
{
	return detail::llround_impl(arg);
}

inline BKSGE_CONSTEXPR long long
llroundl(long double arg) BKSGE_NOEXCEPT
{
	return detail::llround_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR long long
llround(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::llround_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_LLROUND_HPP
