/**
 *	@file	smoothstep_inl.hpp
 *
 *	@brief	smoothstep 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_SMOOTHSTEP_INL_HPP
#define BKSGE_FND_CMATH_INL_SMOOTHSTEP_INL_HPP

#include <bksge/fnd/cmath/smoothstep.hpp>
#include <bksge/fnd/cmath/saturate.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <limits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
smoothstep_uncheck_1(T t) BKSGE_NOEXCEPT
{
	return t * t * (T(3) - (T(2) * t));
}

template <typename T>
inline BKSGE_CONSTEXPR T
smoothstep_uncheck(T from, T to, T x) BKSGE_NOEXCEPT
{
	return smoothstep_uncheck_1(bksge::saturate((x - from) / (to - from)));
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
smoothstep_impl(FloatType from, FloatType to, FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(from) || bksge::isnan(to) || bksge::isnan(x) || from > to ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x >= to ?
			FloatType(1) :
		x <= from ?
			FloatType(0) :
		from == to ?
			FloatType(1) :
		bksge::isinf(from) && bksge::isinf(to) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(from) ?
			FloatType(1) :
		bksge::isinf(to) ?
			FloatType(0) :
		smoothstep_uncheck(from, to, x);
}

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename ArithmeticType3, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2, ArithmeticType3>
smoothstep(ArithmeticType1 from, ArithmeticType2 to, ArithmeticType3 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType1, ArithmeticType2, ArithmeticType3>;
	return detail::smoothstep_impl(static_cast<type>(from), static_cast<type>(to), static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_SMOOTHSTEP_INL_HPP
