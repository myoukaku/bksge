/**
 *	@file	atan2_inl.hpp
 *
 *	@brief	atan2 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ATAN2_INL_HPP
#define BKSGE_FND_CMATH_INL_ATAN2_INL_HPP

#include <bksge/fnd/cmath/atan2.hpp>
#include <bksge/fnd/cmath/atan.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
atan2_unchecked(float y, float x) BKSGE_NOEXCEPT
{
	return __builtin_atan2f(y, x);
}

inline BKSGE_CONSTEXPR double
atan2_unchecked(double y, double x) BKSGE_NOEXCEPT
{
	return __builtin_atan2(y, x);
}

inline BKSGE_CONSTEXPR long double
atan2_unchecked(long double y, long double x) BKSGE_NOEXCEPT
{
	return __builtin_atan2l(y, x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
atan2_unchecked(T y, T x) BKSGE_NOEXCEPT
{
	return std::atan2(y, x);//bksge::atan(y / x) + ((x < 0) ? bksge::copysign(bksge::pi_t<T>(), y) : 0);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
atan2_impl(FloatType y, FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(y) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		bksge::iszero(y) ?
			bksge::signbit(x) ?
				bksge::copysign(bksge::pi_t<FloatType>(), y) :
				bksge::copysign(FloatType(0), y) :
		bksge::isinf(y) ?
			bksge::isinf(x) ?
				bksge::signbit(x) ?
					bksge::copysign(bksge::pi_t<FloatType>()*3/4, y) :
					bksge::copysign(bksge::pi_t<FloatType>()/4, y) :
				bksge::copysign(bksge::pi_t<FloatType>()/2, y) :
		bksge::iszero(x) ?
			bksge::copysign(bksge::pi_t<FloatType>()/2, y) :
		bksge::isinf(x) && bksge::isfinite(y) ?
			bksge::signbit(x) ?
				bksge::copysign(bksge::pi_t<FloatType>(), y) :
				bksge::copysign(FloatType(0), y) :
		atan2_unchecked(y, x);
}

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
atan2(ArithmeticType1 y, ArithmeticType2 x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType1, ArithmeticType2>;
	return detail::atan2_impl(static_cast<type>(y), static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ATAN2_INL_HPP
