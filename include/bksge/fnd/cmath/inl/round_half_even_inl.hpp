/**
 *	@file	round_half_even_inl.hpp
 *
 *	@brief	round_half_even 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ROUND_HALF_EVEN_INL_HPP
#define BKSGE_FND_CMATH_INL_ROUND_HALF_EVEN_INL_HPP

#include <bksge/fnd/cmath/round_half_even.hpp>
#include <bksge/fnd/cmath/ceil.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
round_half_even_unchecked(T x, T h = T(0.5)) BKSGE_NOEXCEPT
{
	return bksge::ceil((x - h) * h) + bksge::floor((x + h) * h);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
round_half_even_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) || bksge::iszero(x) ?
			x :
		round_half_even_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
round_half_even(ArithmeticType x)
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::round_half_even_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ROUND_HALF_EVEN_INL_HPP
