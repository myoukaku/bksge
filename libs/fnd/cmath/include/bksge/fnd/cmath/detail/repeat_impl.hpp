/**
 *	@file	repeat_impl.hpp
 *
 *	@brief	repeat 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_REPEAT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_REPEAT_IMPL_HPP

#include <bksge/fnd/cmath/floor.hpp>
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
repeat_unchecked(T t, T length) BKSGE_NOEXCEPT
{
	return t - bksge::floor(t / length) * length;
}

template <typename T>
inline BKSGE_CONSTEXPR T
repeat_unchecked(T x, T min, T max) BKSGE_NOEXCEPT
{
	return min + repeat_unchecked(x - min, max - min);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
repeat_impl(FloatType x, FloatType min, FloatType max) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x)   ||
		bksge::isnan(min) ||
		bksge::isnan(max) ||
		bksge::isinf(x)   ||
		bksge::isinf(min) ||
		bksge::isinf(max) ||
		min > max ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		min == max ?
			min :
		repeat_unchecked(x, min, max);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_REPEAT_IMPL_HPP
