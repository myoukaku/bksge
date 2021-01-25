/**
 *	@file	acos_inl.hpp
 *
 *	@brief	acos 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ACOS_INL_HPP
#define BKSGE_FND_CMATH_INL_ACOS_INL_HPP

#include <bksge/fnd/cmath/acos.hpp>
#include <bksge/fnd/cmath/asin.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
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
acos_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_acosf(x);
}

inline BKSGE_CONSTEXPR double
acos_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_acos(x);
}

inline BKSGE_CONSTEXPR long double
acos_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_acosl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
acos_unchecked(T x) BKSGE_NOEXCEPT
{
	//return bksge::half_pi<T>() - bksge::asin(x);
	return std::acos(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
acos_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			x :
		bksge::fabs(x) > FloatType(1) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		x == FloatType(1) ?
			FloatType(0) :
		acos_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
acos(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::acos_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ACOS_INL_HPP
