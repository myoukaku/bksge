/**
 *	@file	log1p_impl.hpp
 *
 *	@brief	log1p 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LOG1P_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LOG1P_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/cmath/signbit.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
log1p_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_log1pf(x);
}

inline BKSGE_CONSTEXPR double
log1p_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_log1p(x);
}

inline BKSGE_CONSTEXPR long double
log1p_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_log1pl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
log1p_unchecked(T x) BKSGE_NOEXCEPT
{
//	return bksge::log(T(1) + x);
	return std::log1p(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
log1p_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		x == -1 ?
			-std::numeric_limits<FloatType>::infinity() :
		x < -1 ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) ? //&& !bksge::signbit(x) ?
			std::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		log1p_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LOG1P_IMPL_HPP
