/**
 *	@file	tgamma_impl.hpp
 *
 *	@brief	tgamma 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_TGAMMA_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_TGAMMA_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/is_integer.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
tgamma_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_tgammaf(x);
}

inline BKSGE_CONSTEXPR double
tgamma_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_tgamma(x);
}

inline BKSGE_CONSTEXPR long double
tgamma_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_tgammal(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
tgamma_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::tgamma(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
tgamma_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::iszero(x) ?
			std::numeric_limits<FloatType>::infinity() :
		(x < 0 && bksge::is_integer(x)) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x)  ?
			bksge::signbit(x) ?
				std::numeric_limits<FloatType>::quiet_NaN() :
			std::numeric_limits<FloatType>::infinity() :
		tgamma_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_TGAMMA_IMPL_HPP
