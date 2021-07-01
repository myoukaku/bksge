/**
 *	@file	ilogb_impl.hpp
 *
 *	@brief	ilogb 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ILOGB_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ILOGB_IMPL_HPP

#include <bksge/fnd/cmath/logb.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>	// FP_ILOGB0, FP_ILOGBNAN
#include <climits>	// INT_MAX

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR int
ilogb_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_ilogbf(x);
}

inline BKSGE_CONSTEXPR int
ilogb_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_ilogb(x);
}

inline BKSGE_CONSTEXPR int
ilogb_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_ilogbl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR int
ilogb_unchecked(T x) BKSGE_NOEXCEPT
{
	return static_cast<int>(bksge::detail::logb_unchecked(x));
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR int
ilogb_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			FP_ILOGB0 :
		bksge::isinf(x) ?
			INT_MAX :
		bksge::isnan(x) ?
			FP_ILOGBNAN :
		ilogb_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ILOGB_IMPL_HPP
