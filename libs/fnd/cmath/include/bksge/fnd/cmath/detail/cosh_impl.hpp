/**
 *	@file	cosh_impl.hpp
 *
 *	@brief	cosh 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_COSH_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_COSH_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <cmath>	// TODO
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
cosh_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_coshf(x);
}

inline BKSGE_CONSTEXPR double
cosh_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_cosh(x);
}

inline BKSGE_CONSTEXPR long double
cosh_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_coshl(x);
}

#else

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
cosh_unchecked(FloatType x) BKSGE_NOEXCEPT
{
	return std::cosh(x);	// TODO
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
cosh_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			FloatType(1) :
		bksge::isinf(x) ?
			std::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		cosh_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_COSH_IMPL_HPP
