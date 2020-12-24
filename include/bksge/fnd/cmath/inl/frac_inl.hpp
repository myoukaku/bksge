/**
 *	@file	frac_inl.hpp
 *
 *	@brief	frac 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_FRAC_INL_HPP
#define BKSGE_FND_CMATH_INL_FRAC_INL_HPP

#include <bksge/fnd/cmath/frac.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/type_traits/is_floating_point.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/limits.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
frac_unchecked(T x) BKSGE_NOEXCEPT
{
	return x - bksge::floor(x);
}

template <
	typename FloatType,
	typename = bksge::enable_if_t<
		bksge::is_floating_point<FloatType>::value
	>
>
inline BKSGE_CONSTEXPR FloatType
frac_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) ?
			FloatType(0) :
		frac_unchecked(x);
}

template <
	typename IntegralType,
	typename Promoted = bksge::float_promote_t<IntegralType>,
	typename = bksge::enable_if_t<
		bksge::is_integral<IntegralType>::value
	>
>
inline BKSGE_CONSTEXPR Promoted
frac_impl(IntegralType) BKSGE_NOEXCEPT
{
	return Promoted(0);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
frac(ArithmeticType x) BKSGE_NOEXCEPT
{
	return detail::frac_impl(x);
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_FRAC_INL_HPP
