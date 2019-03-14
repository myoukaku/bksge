/**
 *	@file	lerp_inl.hpp
 *
 *	@brief	lerp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_LERP_INL_HPP
#define BKSGE_CMATH_INL_LERP_INL_HPP

#include <bksge/cmath/lerp.hpp>
#include <bksge/cmath/isinf.hpp>
#include <bksge/cmath/isnan.hpp>
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
lerp_unchecked(T from, T to, T t) BKSGE_NOEXCEPT
{
	return from + (to - from) * t;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
lerp_impl(FloatType from, FloatType to, FloatType t) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(from) ||
		bksge::isnan(to)   ||
		bksge::isnan(t)    ||
		bksge::isinf(from) ||
		bksge::isinf(to) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(t) ?
			t :
		(from == to) ?
			from :
		lerp_unchecked(from, to, t);
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
lerp(
	ArithmeticType1 from,
	ArithmeticType2 to,
	ArithmeticType3 t) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<
		ArithmeticType1,
		ArithmeticType2,
		ArithmeticType3
	>;

	return detail::lerp_impl(
		static_cast<type>(from),
		static_cast<type>(to),
		static_cast<type>(t));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_LERP_INL_HPP
