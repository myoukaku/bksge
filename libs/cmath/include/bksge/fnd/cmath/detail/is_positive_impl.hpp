/**
 *	@file	is_positive_impl.hpp
 *
 *	@brief	is_positive 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_IS_POSITIVE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_IS_POSITIVE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, FloatType)>
inline BKSGE_CONSTEXPR bool
is_positive_impl_2(FloatType x, bksge::detail::overload_priority<1>)
{
	return !bksge::isnan(x) && (x > 0);
}

template <typename IntegralType>
inline BKSGE_CONSTEXPR bool
is_positive_impl_2(IntegralType x, bksge::detail::overload_priority<0>)
{
	return x > 0;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
is_positive_impl(FloatType x) BKSGE_NOEXCEPT
{
	return is_positive_impl_2(x, bksge::detail::overload_priority<1>{});
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_IS_POSITIVE_IMPL_HPP
