/**
 *	@file	is_negative_impl.hpp
 *
 *	@brief	is_negative 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_IS_NEGATIVE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_IS_NEGATIVE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/signed_integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, FloatType)>
inline BKSGE_CONSTEXPR bool
is_negative_impl_2(FloatType x, bksge::detail::overload_priority<2>)
{
	return !bksge::isnan(x) && (x < 0);
}

template <BKSGE_REQUIRES_PARAM(bksge::signed_integral, SignedType)>
inline BKSGE_CONSTEXPR bool
is_negative_impl_2(SignedType x, bksge::detail::overload_priority<1>)
{
	return x < 0;
}

template <typename UnsignedType>
inline BKSGE_CONSTEXPR bool
is_negative_impl_2(UnsignedType /*x*/, bksge::detail::overload_priority<0>)
{
	return false;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
is_negative_impl(T x) BKSGE_NOEXCEPT
{
	return is_negative_impl_2(x, bksge::detail::overload_priority<2>{});
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_IS_NEGATIVE_IMPL_HPP
