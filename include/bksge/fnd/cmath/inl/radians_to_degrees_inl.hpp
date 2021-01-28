/**
 *	@file	radians_to_degrees_inl.hpp
 *
 *	@brief	radians_to_degrees 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_RADIANS_TO_DEGREES_INL_HPP
#define BKSGE_FND_CMATH_INL_RADIANS_TO_DEGREES_INL_HPP

#include <bksge/fnd/cmath/radians_to_degrees.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
radians_to_degrees_unchecked(T x) BKSGE_NOEXCEPT
{
	return x * 180 / bksge::pi_t<T>();
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
radians_to_degrees_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) ?
			x :
		radians_to_degrees_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
radians_to_degrees(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::radians_to_degrees_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_RADIANS_TO_DEGREES_INL_HPP
