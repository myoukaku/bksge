/**
 *	@file	sin_impl.hpp
 *
 *	@brief	sin 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SIN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SIN_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
sin_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_sinf(x);
}

inline BKSGE_CONSTEXPR double
sin_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_sin(x);
}

inline BKSGE_CONSTEXPR long double
sin_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_sinl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
sin_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::sin(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
sin_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::isinf(x) || bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		sin_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SIN_IMPL_HPP
