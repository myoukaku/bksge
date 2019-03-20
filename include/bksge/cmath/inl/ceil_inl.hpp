/**
 *	@file	ceil_inl.hpp
 *
 *	@brief	ceil 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_CEIL_INL_HPP
#define BKSGE_CMATH_INL_CEIL_INL_HPP

#include <bksge/cmath/ceil.hpp>
#include <bksge/cmath/iszero.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/cmath/isinf.hpp>
#include <bksge/cmath/almost_equal.hpp>
#include <bksge/cmath/trunc.hpp>
#include <bksge/type_traits/float_promote.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
ceil_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_ceilf(x);
}

inline BKSGE_CONSTEXPR double
ceil_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_ceil(x);
}

inline BKSGE_CONSTEXPR long double
ceil_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_ceill(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
ceil_unchecked_1(T x, T x0) BKSGE_NOEXCEPT
{
	return
		x < 0 || bksge::almost_equal(x, x0) ?
			x0 :
		x0 + T(1);
}

template <typename T>
inline BKSGE_CONSTEXPR T
ceil_unchecked(T x) BKSGE_NOEXCEPT
{
	return ceil_unchecked_1(x, trunc_unchecked(x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
ceil_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		(bksge::iszero(x) || bksge::isnan(x) || bksge::isinf(x)) ?
			x :
		ceil_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
ceil(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::ceil_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_CEIL_INL_HPP
