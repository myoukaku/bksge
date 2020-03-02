/**
 *	@file	almost_equal_inl.hpp
 *
 *	@brief	almost_equal 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ALMOST_EQUAL_INL_HPP
#define BKSGE_FND_CMATH_INL_ALMOST_EQUAL_INL_HPP

#include <bksge/fnd/cmath/almost_equal.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/arithmetic_promote.hpp>
#include <bksge/fnd/type_traits/is_floating_point.hpp>
#include <limits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T const&
tmax(T const& a, T const& b)
{
	return b < a ? a : b;
}

template <typename T, bool = bksge::is_floating_point<T>::value>
struct almost_equal_impl;

template <typename FloatType>
struct almost_equal_impl<FloatType, true>
{
	static BKSGE_CONSTEXPR bool invoke(FloatType x, FloatType y) BKSGE_NOEXCEPT
	{
		return
			(bksge::isnan(x) || bksge::isnan(y) || bksge::isinf(x) || bksge::isinf(y)) ?
				x == y :
			x == y ||
			bksge::fabs(x - y) <=
				std::numeric_limits<FloatType>::epsilon() *
				tmax(tmax(bksge::fabs(x), bksge::fabs(y)), FloatType(1));
	}
};

template <typename IntType>
struct almost_equal_impl<IntType, false>
{
	static BKSGE_CONSTEXPR bool invoke(IntType x, IntType y) BKSGE_NOEXCEPT
	{
		return x == y;
	}
};

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename>
inline BKSGE_CONSTEXPR bool
almost_equal(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT
{
	using type = bksge::arithmetic_promote_t<ArithmeticType1, ArithmeticType2>;
	return detail::almost_equal_impl<type>::invoke(x, y);
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ALMOST_EQUAL_INL_HPP
