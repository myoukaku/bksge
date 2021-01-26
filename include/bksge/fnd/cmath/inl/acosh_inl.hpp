/**
 *	@file	acosh_inl.hpp
 *
 *	@brief	acosh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ACOSH_INL_HPP
#define BKSGE_FND_CMATH_INL_ACOSH_INL_HPP

#include <bksge/fnd/cmath/acosh.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
acosh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_acoshf(x);
}

inline BKSGE_CONSTEXPR double
acosh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_acosh(x);
}

inline BKSGE_CONSTEXPR long double
acosh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_acoshl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
acosh_unchecked(T x) BKSGE_NOEXCEPT
{
	return bksge::log(x + bksge::sqrt(x * x - 1));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
acosh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		x < FloatType(1) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		x == FloatType(1) ?
			FloatType(0) :
		bksge::isinf(x) ?
			x :
		bksge::isnan(x) ?
			x :
		acosh_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
acosh(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::acosh_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ACOSH_INL_HPP
