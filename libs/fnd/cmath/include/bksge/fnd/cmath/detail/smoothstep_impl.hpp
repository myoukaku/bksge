/**
 *	@file	smoothstep_impl.hpp
 *
 *	@brief	smoothstep 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SMOOTHSTEP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SMOOTHSTEP_IMPL_HPP

#include <bksge/fnd/cmath/saturate.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
smoothstep_uncheck_1(T t) BKSGE_NOEXCEPT
{
	return t * t * (T(3) - (T(2) * t));
}

template <typename T>
inline BKSGE_CONSTEXPR T
smoothstep_uncheck(T from, T to, T x) BKSGE_NOEXCEPT
{
	return smoothstep_uncheck_1(bksge::saturate((x - from) / (to - from)));
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
smoothstep_impl(FloatType from, FloatType to, FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(from) || bksge::isnan(to) || bksge::isnan(x) || from > to ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x >= to ?
			FloatType(1) :
		x <= from ?
			FloatType(0) :
		from == to ?
			FloatType(1) :
		bksge::isinf(from) && bksge::isinf(to) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(from) ?
			FloatType(1) :
		bksge::isinf(to) ?
			FloatType(0) :
		smoothstep_uncheck(from, to, x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SMOOTHSTEP_IMPL_HPP
