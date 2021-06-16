/**
 *	@file	lerp_impl.hpp
 *
 *	@brief	lerp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LERP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LERP_IMPL_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
lerp_impl(T a, T b, T t) BKSGE_NOEXCEPT
{
	if ((a <= 0 && b >= 0) || (a >= 0 && b <= 0))
	{
		return t * b + (1 - t) * a;
	}

	if (t == 1)
	{
		return b;		// exact
	}

	// Exact at t=0, monotonic except near t=1,
	// bounded, determinate, and consistent:
	const T x = a + t * (b - a);
	return (t > 1) == (b > a) ?
		(b < x ? x : b) :
		(b > x ? x : b);  // monotonic near t=1
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LERP_IMPL_HPP
