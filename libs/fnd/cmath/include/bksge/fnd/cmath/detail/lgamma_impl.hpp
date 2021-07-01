/**
 *	@file	lgamma_impl.hpp
 *
 *	@brief	lgamma 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LGAMMA_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LGAMMA_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/is_integer.hpp>
#include <cmath>	// TODO
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
lgamma_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_lgammaf(x);
}

inline BKSGE_CONSTEXPR double
lgamma_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_lgamma(x);
}

inline BKSGE_CONSTEXPR long double
lgamma_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_lgammal(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
lgamma_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::lgamma(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
lgamma_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x == 1 ||
		x == 2 ?
			FloatType(0) :
		bksge::iszero(x) ||
		bksge::isinf(x)  ||
		(x < 0 && bksge::is_integer(x)) ?
			std::numeric_limits<FloatType>::infinity() :
		lgamma_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LGAMMA_IMPL_HPP
