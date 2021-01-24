/**
 *	@file	sqrt_inl.hpp
 *
 *	@brief	sqrt 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_SQRT_INL_HPP
#define BKSGE_FND_CMATH_INL_SQRT_INL_HPP

#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
sqrt_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_sqrtf(x);
}

inline BKSGE_CONSTEXPR double
sqrt_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_sqrt(x);
}

inline BKSGE_CONSTEXPR long double
sqrt_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_sqrtl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
sqrt_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::sqrt(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
sqrt_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		x < 0 ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) || bksge::iszero(x) ?
			x :
		sqrt_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
sqrt(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::sqrt_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_SQRT_INL_HPP
