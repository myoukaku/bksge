/**
 *	@file	isnan.hpp
 *
 *	@brief	isnan 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISNAN_HPP
#define BKSGE_FND_CMATH_ISNAN_HPP

#include <bksge/fnd/cmath/detail/isnan_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	NaNかどうか調べる
 *
 *	@param	arg	調べる値
 *
 *	@return	argがNaNならtrue,そうでないならfalse.
 *
 *	@note	argが整数型のときはdoubleにキャストしてから調べる。
 */
inline BKSGE_CONSTEXPR bool
isnan(float arg) BKSGE_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isnan(double arg) BKSGE_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

inline BKSGE_CONSTEXPR bool
isnan(long double arg) BKSGE_NOEXCEPT
{
	return detail::isnan_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR bool
isnan(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::isnan_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_ISNAN_HPP
