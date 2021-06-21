/**
 *	@file	fma_impl.hpp
 *
 *	@brief	fma 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FMA_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FMA_IMPL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
fma_unchecked(float x, float y, float z) BKSGE_NOEXCEPT
{
	return __builtin_fmaf(x, y, z);
}

inline BKSGE_CONSTEXPR double
fma_unchecked(double x, double y, double z) BKSGE_NOEXCEPT
{
	return __builtin_fma(x, y, z);
}

inline BKSGE_CONSTEXPR long double
fma_unchecked(long double x, long double y, long double z) BKSGE_NOEXCEPT
{
	return __builtin_fmal(x, y, z);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
fma_unchecked(T x, T y, T z) BKSGE_NOEXCEPT
{
	return x * y + z;
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fma_impl(FloatType x, FloatType y, FloatType z) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ||
		bksge::isnan(y) ||
		bksge::isnan(z) ||
		(bksge::isinf(x) && bksge::iszero(y)) ||
		(bksge::iszero(x) && bksge::isinf(y)) ||
		((bksge::isinf(x) || bksge::isinf(y)) && bksge::isinf(z) && (bksge::signbit(x) ^ bksge::signbit(y) ^ bksge::signbit(z))) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		fma_unchecked(x, y, z);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FMA_IMPL_HPP
