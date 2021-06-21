/**
 *	@file	almost_equal_impl.hpp
 *
 *	@brief	almost_equal 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ALMOST_EQUAL_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ALMOST_EQUAL_IMPL_HPP

#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_floating_point.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
tmax(T const& a, T const& b)
{
	return b < a ? a : b;
}

template <typename FloatType, typename = bksge::enable_if_t<bksge::is_floating_point<FloatType>::value>>
inline BKSGE_CONSTEXPR bool
almost_equal_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		(bksge::isnan(x) || bksge::isnan(y) || bksge::isinf(x) || bksge::isinf(y)) ?
			x == y :
		x == y ||
		bksge::fabs(x - y) <=
			std::numeric_limits<FloatType>::epsilon() *
			tmax(tmax(bksge::fabs(x), bksge::fabs(y)), FloatType(1));
}

template <typename IntType, bksge::enable_if_t<!bksge::is_floating_point<IntType>::value>* = nullptr>
inline BKSGE_CONSTEXPR bool
almost_equal_impl(IntType x, IntType y) BKSGE_NOEXCEPT
{
	return x == y;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ALMOST_EQUAL_IMPL_HPP
