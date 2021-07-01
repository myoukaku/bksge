/**
 *	@file	log_impl.hpp
 *
 *	@brief	log 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LOG_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LOG_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <cmath>	// TODO
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
log_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_logf(x);
}

inline BKSGE_CONSTEXPR double
log_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_log(x);
}

inline BKSGE_CONSTEXPR long double
log_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_logl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
log_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::log(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
log_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::iszero(x) ?
			-std::numeric_limits<FloatType>::infinity() :
		x == FloatType(1) ?
			FloatType(0) :
		x < FloatType(0) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) ?
			std::numeric_limits<FloatType>::infinity() :
		log_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LOG_IMPL_HPP
