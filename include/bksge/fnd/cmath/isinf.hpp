/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISINF_HPP
#define BKSGE_FND_CMATH_ISINF_HPP

#include <bksge/fnd/cmath/detail/isinf_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	∞かどうか調べる
 *
 *	@param	arg	調べる値
 *
 *	@return	argが±∞ならtrue,そうでないならfalse.
 *
 *	@note	argが整数型のときはdoubleにキャストしてから調べる。
 */
inline BKSGE_CONSTEXPR bool
isinf(float arg) BKSGE_NOEXCEPT
{
	return detail::isinf_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isinf(double arg) BKSGE_NOEXCEPT
{
	return detail::isinf_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isinf(long double arg) BKSGE_NOEXCEPT
{
	return detail::isinf_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR bool
isinf(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::isinf_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISINF_HPP
