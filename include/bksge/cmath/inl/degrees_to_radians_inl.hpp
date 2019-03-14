/**
 *	@file	degrees_to_radians_inl.hpp
 *
 *	@brief	degrees_to_radians 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_DEGREES_TO_RADIANS_INL_HPP
#define BKSGE_CMATH_INL_DEGREES_TO_RADIANS_INL_HPP

#include <bksge/cmath/degrees_to_radians.hpp>
#include <bksge/cmath/isinf.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/cmath/constants.hpp>
#include <bksge/type_traits/float_promote.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
degrees_to_radians_unchecked(T x) BKSGE_NOEXCEPT
{
	return x * bksge::pi<T>() / 180;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
degrees_to_radians_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) ?
			x :
		degrees_to_radians_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
degrees_to_radians(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::degrees_to_radians_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_DEGREES_TO_RADIANS_INL_HPP
