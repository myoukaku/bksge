/**
 *	@file	fabs_inl.hpp
 *
 *	@brief	fabs 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_FABS_INL_HPP
#define BKSGE_CMATH_INL_FABS_INL_HPP

#include <bksge/cmath/fabs.hpp>
#include <bksge/cmath/copysign.hpp>
#include <bksge/type_traits/float_promote.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
fabs_impl(float x) BKSGE_NOEXCEPT
{
	return __builtin_fabsf(x);
}

inline BKSGE_CONSTEXPR double
fabs_impl(double x) BKSGE_NOEXCEPT
{
	return __builtin_fabs(x);
}

inline BKSGE_CONSTEXPR long double
fabs_impl(long double x) BKSGE_NOEXCEPT
{
	return __builtin_fabsl(x);
}

#else

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fabs_impl(FloatType x) BKSGE_NOEXCEPT
{
	return bksge::copysign(x, FloatType(1));
}

#endif

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
fabs(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::fabs_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_FABS_INL_HPP
