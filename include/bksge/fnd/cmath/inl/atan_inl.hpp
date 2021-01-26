/**
 *	@file	atan_inl.hpp
 *
 *	@brief	atan 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ATAN_INL_HPP
#define BKSGE_FND_CMATH_INL_ATAN_INL_HPP

#include <bksge/fnd/cmath/atan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>	// TODO

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
atan_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_atanf(x);
}

inline BKSGE_CONSTEXPR double
atan_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_atan(x);
}

inline BKSGE_CONSTEXPR long double
atan_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_atanl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
atan_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::atan(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
atan_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::isinf(x) ?
			bksge::copysign(bksge::half_pi<FloatType>(), x) :
		bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		atan_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
atan(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::atan_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ATAN_INL_HPP
