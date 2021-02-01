/**
 *	@file	iszero.hpp
 *
 *	@brief	iszero 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISZERO_HPP
#define BKSGE_FND_CMATH_ISZERO_HPP

#include <bksge/fnd/cmath/detail/iszero_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	0かどうか調べる
 *
 *	@param	arg	調べる値
 *
 *	@return	argが±0ならtrue,そうでないならfalse.
 *
 *	@note	argが整数型のときはdoubleにキャストしてから調べる。
 */
inline BKSGE_CONSTEXPR bool
iszero(float arg) BKSGE_NOEXCEPT
{
	return detail::iszero_impl(arg);
}

inline BKSGE_CONSTEXPR bool
iszero(double arg) BKSGE_NOEXCEPT
{
	return detail::iszero_impl(arg);
}

inline BKSGE_CONSTEXPR bool
iszero(long double arg) BKSGE_NOEXCEPT
{
	return detail::iszero_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR bool
iszero(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::iszero_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISZERO_HPP
