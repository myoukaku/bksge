/**
 *	@file	signbit_inl.hpp
 *
 *	@brief	signbit 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_SIGNBIT_INL_HPP
#define BKSGE_FND_CMATH_INL_SIGNBIT_INL_HPP

#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
signbit_impl(FloatType x) BKSGE_NOEXCEPT
{
	return __builtin_signbit(x);
}

#else

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
signbit_impl(FloatType x) BKSGE_NOEXCEPT
{
	return (bksge::iszero(x) || bksge::isnan(x)) ?
		false :
		(x < FloatType(0));
}

#endif

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bool
signbit(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::signbit_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_SIGNBIT_INL_HPP
