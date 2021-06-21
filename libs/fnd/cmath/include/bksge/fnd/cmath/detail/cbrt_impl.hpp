/**
 *	@file	cbrt_impl.hpp
 *
 *	@brief	cbrt 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_CBRT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_CBRT_IMPL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/cmath/pow.hpp>
//#include <bksge/fnd/cmath/constants.hpp>
#include <cmath>	// TODO
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
cbrt_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_cbrtf(x);
}

inline BKSGE_CONSTEXPR double
cbrt_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_cbrt(x);
}

inline BKSGE_CONSTEXPR long double
cbrt_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_cbrtl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
cbrt_unchecked(T x) BKSGE_NOEXCEPT
{
	//return x < 0 ?
	//	-bksge::pow(-x, bksge::third<T>()) :
	//	 bksge::pow( x, bksge::third<T>());

	return std::cbrt(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
cbrt_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::iszero(x) ?
			x :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		cbrt_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_CBRT_IMPL_HPP
