/**
 *	@file	isfinite.hpp
 *
 *	@brief	isfinite 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISFINITE_HPP
#define BKSGE_FND_CMATH_ISFINITE_HPP

#include <bksge/fnd/cmath/detail/isfinite_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	有限の値かどうか調べる
 *
 *	@param	arg	調べる値
 *
 *	@return	argが有限の値ならtrue,∞またはNaNならfalse.
 *
 *	@note	argが整数型のときはdoubleにキャストしてから調べる。
 */
inline BKSGE_CONSTEXPR bool
isfinite(float arg) BKSGE_NOEXCEPT
{
	return detail::isfinite_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isfinite(double arg) BKSGE_NOEXCEPT
{
	return detail::isfinite_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isfinite(long double arg) BKSGE_NOEXCEPT
{
	return detail::isfinite_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR bool
isfinite(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::isfinite_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISFINITE_HPP
