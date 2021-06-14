/**
 *	@file	asinh_impl.hpp
 *
 *	@brief	asinh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ASINH_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ASINH_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
asinh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_asinhf(x);
}

inline BKSGE_CONSTEXPR double
asinh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_asinh(x);
}

inline BKSGE_CONSTEXPR long double
asinh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_asinhl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
asinh_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::asinh(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
asinh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) || bksge::isinf(x) || bksge::isnan(x) ?
			x :
		asinh_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ASINH_IMPL_HPP
