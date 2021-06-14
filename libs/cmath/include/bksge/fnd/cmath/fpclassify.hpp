/**
 *	@file	fpclassify.hpp
 *
 *	@brief	fpclassify 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FPCLASSIFY_HPP
#define BKSGE_FND_CMATH_FPCLASSIFY_HPP

#include <bksge/fnd/cmath/detail/fpclassify_impl.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline BKSGE_CONSTEXPR int
fpclassify(float arg) BKSGE_NOEXCEPT
{
	return detail::fpclassify_impl(arg);
}

inline BKSGE_CONSTEXPR int
fpclassify(double arg) BKSGE_NOEXCEPT
{
	return detail::fpclassify_impl(arg);
}

inline BKSGE_CONSTEXPR int
fpclassify(long double arg) BKSGE_NOEXCEPT
{
	return detail::fpclassify_impl(arg);
}

template <BKSGE_REQUIRES_PARAM(bksge::integral, IntegralType)>
inline BKSGE_CONSTEXPR int
fpclassify(IntegralType arg) BKSGE_NOEXCEPT
{
	return detail::fpclassify_impl(static_cast<double>(arg));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FPCLASSIFY_HPP
