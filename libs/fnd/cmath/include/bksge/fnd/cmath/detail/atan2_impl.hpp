/**
 *	@file	atan2_impl.hpp
 *
 *	@brief	atan2 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ATAN2_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ATAN2_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
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
	return std::atan2(y, x);
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

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ATAN2_IMPL_HPP
