/**
 *	@file	abs_impl.hpp
 *
 *	@brief	abs 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ABS_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ABS_IMPL_HPP

#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
inline BKSGE_CONSTEXPR T
abs_impl_2(T x, bksge::detail::overload_priority<2>) BKSGE_NOEXCEPT
{
	return bksge::fabs(x);
}

template <BKSGE_REQUIRES_PARAM(bksge::unsigned_integral, T)>
inline BKSGE_CONSTEXPR T
abs_impl_2(T x, bksge::detail::overload_priority<1>) BKSGE_NOEXCEPT
{
	return x;
}

template <typename T>
inline BKSGE_CONSTEXPR T
abs_impl_2(T x, bksge::detail::overload_priority<0>) BKSGE_NOEXCEPT
{
	return x < 0 ? -x : x;
}

template <typename T>
inline BKSGE_CONSTEXPR T
abs_impl(T x) BKSGE_NOEXCEPT
{
	return abs_impl_2(x, bksge::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ABS_IMPL_HPP
