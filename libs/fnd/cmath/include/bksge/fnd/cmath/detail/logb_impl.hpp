/**
 *	@file	logb_impl.hpp
 *
 *	@brief	logb 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LOGB_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LOGB_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>	// TODO
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
logb_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_logbf(x);
}

inline BKSGE_CONSTEXPR double
logb_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_logb(x);
}

inline BKSGE_CONSTEXPR long double
logb_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_logbl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
logb_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::logb(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
logb_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			-std::numeric_limits<FloatType>::infinity() :
		bksge::isinf(x) ?
			std::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		logb_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LOGB_IMPL_HPP
