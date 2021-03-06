﻿/**
 *	@file	tan_impl.hpp
 *
 *	@brief	tan 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_TAN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_TAN_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
//#include <bksge/fnd/cmath/sin.hpp>
//#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
tan_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_tanf(x);
}

inline BKSGE_CONSTEXPR double
tan_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_tan(x);
}

inline BKSGE_CONSTEXPR long double
tan_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_tanl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
tan_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::tan(x);
//	return bksge::sin(x) / bksge::cos(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
tan_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			x :
		bksge::isinf(x) || bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		tan_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_TAN_IMPL_HPP
