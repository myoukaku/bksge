/**
 *	@file	atan_impl.hpp
 *
 *	@brief	atan 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ATAN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ATAN_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/numbers.hpp>
#include <cmath>	// TODO
#include <limits>

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
			bksge::copysign(bksge::pi_t<FloatType>() / 2, x) :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		atan_unchecked(x);
}

}	// namespace detail


}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ATAN_IMPL_HPP
