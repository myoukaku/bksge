/**
 *	@file	atanh_inl.hpp
 *
 *	@brief	atanh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ATANH_INL_HPP
#define BKSGE_FND_CMATH_INL_ATANH_INL_HPP

#include <bksge/fnd/cmath/atanh.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/log.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
atanh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_atanhf(x);
}

inline BKSGE_CONSTEXPR double
atanh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_atanh(x);
}

inline BKSGE_CONSTEXPR long double
atanh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_atanhl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
atanh_unchecked(T x) BKSGE_NOEXCEPT
{
//	return bksge::log((1 + x) / (1 - x)) / 2;
	return std::atanh(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
atanh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		x == FloatType(1) ?
			bksge::numeric_limits<FloatType>::infinity() :
		x == FloatType(-1) ?
			-bksge::numeric_limits<FloatType>::infinity() :
		bksge::fabs(x) > FloatType(1) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		atanh_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
atanh(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::atanh_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ATANH_INL_HPP
