/**
 *	@file	log10_impl.hpp
 *
 *	@brief	log10 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LOG10_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LOG10_IMPL_HPP

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
log10_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_log10f(x);
}

inline BKSGE_CONSTEXPR double
log10_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_log10(x);
}

inline BKSGE_CONSTEXPR long double
log10_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_log10l(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
log10_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::log10(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
log10_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			-std::numeric_limits<FloatType>::infinity() :
		x == FloatType(1) ?
			FloatType(0) :
		x < FloatType(0) || bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) ?
			std::numeric_limits<FloatType>::infinity() :
		log10_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LOG10_IMPL_HPP
