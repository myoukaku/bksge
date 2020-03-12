/**
 *	@file	sin_inl.hpp
 *
 *	@brief	sin 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_SIN_INL_HPP
#define BKSGE_FND_CMATH_INL_SIN_INL_HPP

#include <bksge/fnd/cmath/sin.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <limits>
#include <cmath>

namespace bksge
{

namespace cmath
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
sin_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_sinf(x);
}

inline BKSGE_CONSTEXPR double
sin_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_sin(x);
}

inline BKSGE_CONSTEXPR long double
sin_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_sinl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
sin_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::sin(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
sin_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::isinf(x) || bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		sin_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
sin(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::sin_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_SIN_INL_HPP
