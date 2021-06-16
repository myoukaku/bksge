/**
 *	@file	round_impl.hpp
 *
 *	@brief	round 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ROUND_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ROUND_IMPL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/trunc.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
round_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_roundf(x);
}

inline BKSGE_CONSTEXPR double
round_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_round(x);
}

inline BKSGE_CONSTEXPR long double
round_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_roundl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
round_unchecked_1(T x, T x0) BKSGE_NOEXCEPT
{
	return bksge::fabs(x - x0) < T(0.5) ?
		x0 :
		x0 + (x < 0 ? -T(1) : T(1));
}

template <typename T>
inline BKSGE_CONSTEXPR T
round_unchecked(T x) BKSGE_NOEXCEPT
{
	return round_unchecked_1(x, trunc_unchecked(x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
round_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) || bksge::iszero(x) ?
			x :
		round_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ROUND_IMPL_HPP
