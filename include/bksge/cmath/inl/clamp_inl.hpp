/**
 *	@file	clamp_inl.hpp
 *
 *	@brief	clamp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_CLAMP_INL_HPP
#define BKSGE_CMATH_INL_CLAMP_INL_HPP

#include <bksge/cmath/clamp.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/algorithm/max.hpp>
#include <bksge/algorithm/min.hpp>
#include <bksge/type_traits/float_promote.hpp>
#include <limits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
clamp_unchecked(T x, T min_value, T max_value) BKSGE_NOEXCEPT
{
	return bksge::min(bksge::max(x, min_value), max_value);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
clamp_impl(
	FloatType x,
	FloatType min_value,
	FloatType max_value) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ||
		bksge::isnan(min_value) ||
		bksge::isnan(max_value) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		min_value > max_value ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		clamp_unchecked(x, min_value, max_value);
}

}	// namespace detail

template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename ArithmeticType3,
	typename
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<
	ArithmeticType1,
	ArithmeticType2,
	ArithmeticType3
>
clamp(
	ArithmeticType1 x,
	ArithmeticType2 min,
	ArithmeticType3 max) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<
		ArithmeticType1,
		ArithmeticType2,
		ArithmeticType3
	>;
	return detail::clamp_impl(
		static_cast<type>(x),
		static_cast<type>(min),
		static_cast<type>(max));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_CLAMP_INL_HPP
