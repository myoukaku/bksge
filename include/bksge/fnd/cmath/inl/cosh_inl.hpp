/**
 *	@file	cosh_inl.hpp
 *
 *	@brief	cosh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_COSH_INL_HPP
#define BKSGE_FND_CMATH_INL_COSH_INL_HPP

#include <bksge/fnd/cmath/cosh.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
cosh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_coshf(x);
}

inline BKSGE_CONSTEXPR double
cosh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_cosh(x);
}

inline BKSGE_CONSTEXPR long double
cosh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_coshl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
cosh_unchecked_1(T x) BKSGE_NOEXCEPT
{
	return T(0.5) * x + T(0.5) / x;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
cosh_unchecked(FloatType x) BKSGE_NOEXCEPT
{
	return cosh_unchecked_1(bksge::exp(x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
cosh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			FloatType(1) :
		bksge::isinf(x) ?
			bksge::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		cosh_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
cosh(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::cosh_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_COSH_INL_HPP
