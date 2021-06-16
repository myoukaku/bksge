/**
 *	@file	isnormal.hpp
 *
 *	@brief	isnormal 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISNORMAL_HPP
#define BKSGE_FND_CMATH_ISNORMAL_HPP

#include <bksge/fnd/cmath/detail/isnormal_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	正規化数かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが正規化数ならtrue,そうでないならfalse.
 *
 *	正規化数とは以下の条件を全て満たす数のこと:
 *	・ゼロでない
 *	・非正規化数でない
 *	・無限大でない
 *	・NaNでない
 *
 *	@note	ArithmeticTypeが整数型のときはdoubleにキャストしてから調べる。
 */
inline BKSGE_CONSTEXPR bool
isnormal(float arg) BKSGE_NOEXCEPT
{
	return detail::isnormal_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isnormal(double arg) BKSGE_NOEXCEPT
{
	return detail::isnormal_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isnormal(long double arg) BKSGE_NOEXCEPT
{
	return detail::isnormal_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR bool
isnormal(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::isnormal_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISNORMAL_HPP
