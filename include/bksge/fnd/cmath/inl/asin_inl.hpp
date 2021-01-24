/**
 *	@file	asin_inl.hpp
 *
 *	@brief	asin 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ASIN_INL_HPP
#define BKSGE_FND_CMATH_INL_ASIN_INL_HPP

#include <bksge/fnd/cmath/asin.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
asin_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_asinf(x);
}

inline BKSGE_CONSTEXPR double
asin_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_asin(x);
}

inline BKSGE_CONSTEXPR long double
asin_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_asinl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
asin_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::asin(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
asin_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::fabs(x) > FloatType(1) || bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		asin_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
asin(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::asin_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ASIN_INL_HPP
