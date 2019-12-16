/**
 *	@file	step_inl.hpp
 *
 *	@brief	step 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_STEP_INL_HPP
#define BKSGE_FND_CMATH_INL_STEP_INL_HPP

#include <bksge/fnd/cmath/step.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
step_impl(FloatType a, FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(a) || bksge::isnan(x) ?
			FloatType(0) :
		x >= a ?
			FloatType(1) :
		FloatType(0);
}

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
step(ArithmeticType1 a, ArithmeticType2 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType1, ArithmeticType2>;
	return detail::step_impl(static_cast<type>(a), static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_STEP_INL_HPP
