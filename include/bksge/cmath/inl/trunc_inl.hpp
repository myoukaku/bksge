/**
 *	@file	trunc_inl.hpp
 *
 *	@brief	trunc 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_TRUNC_INL_HPP
#define BKSGE_CMATH_INL_TRUNC_INL_HPP

#include <bksge/cmath/trunc.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/cmath/isinf.hpp>
#include <bksge/cmath/iszero.hpp>
#include <bksge/type_traits/float_promote.hpp>
#include <cstdint>

namespace bksge
{

namespace cmath
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
trunc_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_truncf(x);
}

inline BKSGE_CONSTEXPR double
trunc_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_trunc(x);
}

inline BKSGE_CONSTEXPR long double
trunc_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_truncl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
trunc_unchecked(T x) BKSGE_NOEXCEPT
{
	return x < 0 ?
		-static_cast<T>(static_cast<std::uintmax_t>(-x)) :
		 static_cast<T>(static_cast<std::uintmax_t>( x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
trunc_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isinf(x) || bksge::iszero(x) ?
			x :
		trunc_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
trunc(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::trunc_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_TRUNC_INL_HPP
