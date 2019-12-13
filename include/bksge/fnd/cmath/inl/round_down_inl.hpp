/**
 *	@file	round_down_inl.hpp
 *
 *	@brief	round_down 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ROUND_DOWN_INL_HPP
#define BKSGE_FND_CMATH_INL_ROUND_DOWN_INL_HPP

#include <bksge/fnd/cmath/round_down.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <limits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
round_down_unchecked(T x, T base) BKSGE_NOEXCEPT
{
	return bksge::floor(x / base) * base;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
round_down_impl(FloatType x, FloatType base) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(base) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(base) ?
			base :
		bksge::isinf(x) ?
			x :
		base == 0 ?
			x :
		round_down_unchecked(x, base);
}

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename>
inline BKSGE_CONSTEXPR ArithmeticType1
round_down(ArithmeticType1 x, ArithmeticType2 base) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType1, ArithmeticType2>;
	return static_cast<ArithmeticType1>(detail::round_down_impl(static_cast<type>(x), static_cast<type>(base)));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ROUND_DOWN_INL_HPP
