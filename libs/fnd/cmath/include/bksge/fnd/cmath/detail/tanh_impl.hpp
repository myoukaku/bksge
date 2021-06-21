/**
 *	@file	tanh_impl.hpp
 *
 *	@brief	tanh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_TANH_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_TANH_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <cmath>	// TODO
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
tanh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_tanhf(x);
}

inline BKSGE_CONSTEXPR double
tanh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_tanh(x);
}

inline BKSGE_CONSTEXPR long double
tanh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_tanhl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
tanh_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::tanh(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
tanh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::isinf(x) ?
			bksge::copysign(FloatType(1), x) :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		tanh_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_TANH_IMPL_HPP
