/**
 *	@file	fabs_impl.hpp
 *
 *	@brief	fabs 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FABS_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FABS_IMPL_HPP

#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
fabs_impl(float x) BKSGE_NOEXCEPT
{
	return __builtin_fabsf(x);
}

inline BKSGE_CONSTEXPR double
fabs_impl(double x) BKSGE_NOEXCEPT
{
	return __builtin_fabs(x);
}

inline BKSGE_CONSTEXPR long double
fabs_impl(long double x) BKSGE_NOEXCEPT
{
	return __builtin_fabsl(x);
}

#else

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fabs_impl(FloatType x) BKSGE_NOEXCEPT
{
	return bksge::copysign(x, FloatType(1));
}

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FABS_IMPL_HPP
