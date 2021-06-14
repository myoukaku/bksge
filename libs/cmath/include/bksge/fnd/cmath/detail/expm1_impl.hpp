/**
 *	@file	expm1_impl.hpp
 *
 *	@brief	expm1 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPM1_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPM1_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
expm1_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_expm1f(x);
}

inline BKSGE_CONSTEXPR double
expm1_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_expm1(x);
}

inline BKSGE_CONSTEXPR long double
expm1_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_expm1l(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
expm1_unchecked(T x) BKSGE_NOEXCEPT
{
	return bksge::exp(x) - T(1);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
expm1_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::isinf(x) ?
			bksge::signbit(x) ?
				FloatType(-1) :
			x :
		bksge::isnan(x) ?
			x :
		expm1_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPM1_IMPL_HPP
