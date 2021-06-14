/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SIGNBIT_HPP
#define BKSGE_FND_CMATH_SIGNBIT_HPP

#include <bksge/fnd/cmath/detail/signbit_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	負の値かどうか調べる
 *
 *	@param	arg	調べる値
 *
 *	@return	argが負の値ならtrue,そうでないならfalse.
 *
 *	@note	ArithmeticTypeが整数型のときはdoubleにキャストしてから調べる。
 *
 *	※std::signbitとの違い
 *	argが±0または±NaNのとき、falseを返す。
 *	これはconstexpr関数にするための制限。
 */
inline BKSGE_CONSTEXPR bool
signbit(float arg) BKSGE_NOEXCEPT
{
	return detail::signbit_impl(arg);
}

inline BKSGE_CONSTEXPR bool
signbit(double arg) BKSGE_NOEXCEPT
{
	return detail::signbit_impl(arg);
}

inline BKSGE_CONSTEXPR bool
signbit(long double arg) BKSGE_NOEXCEPT
{
	return detail::signbit_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR bool
signbit(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::signbit_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SIGNBIT_HPP
