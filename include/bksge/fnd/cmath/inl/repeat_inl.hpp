/**
 *	@file	repeat_inl.hpp
 *
 *	@brief	repeat 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_REPEAT_INL_HPP
#define BKSGE_FND_CMATH_INL_REPEAT_INL_HPP

#include <bksge/fnd/cmath/repeat.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
repeat_unchecked(T t, T length) BKSGE_NOEXCEPT
{
	return t - bksge::floor(t / length) * length;
}

template <typename T>
inline BKSGE_CONSTEXPR T
repeat_unchecked(T x, T min, T max) BKSGE_NOEXCEPT
{
	return min + repeat_unchecked(x - min, max - min);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
repeat_impl(FloatType x, FloatType min, FloatType max) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x)   ||
		bksge::isnan(min) ||
		bksge::isnan(max) ||
		bksge::isinf(x)   ||
		bksge::isinf(min) ||
		bksge::isinf(max) ||
		min > max ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		min == max ?
			min :
		repeat_unchecked(x, min, max);
}

}	// namespace detail

template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename ArithmeticType3,
	typename
>
inline BKSGE_CONSTEXPR
bksge::float_promote_t<
	ArithmeticType1,
	ArithmeticType2,
	ArithmeticType3
>
repeat(
	ArithmeticType1 x,
	ArithmeticType2 min,
	ArithmeticType3 max) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<
		ArithmeticType1,
		ArithmeticType2,
		ArithmeticType3
	>;

	return detail::repeat_impl(
		static_cast<type>(x),
		static_cast<type>(min),
		static_cast<type>(max));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_REPEAT_INL_HPP
