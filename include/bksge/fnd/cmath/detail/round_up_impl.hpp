/**
 *	@file	round_up_impl.hpp
 *
 *	@brief	round_up 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ROUND_UP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ROUND_UP_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/ceil.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
round_up_unchecked(T x, T base) BKSGE_NOEXCEPT
{
	return bksge::ceil(x / base) * base;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
round_up_impl(FloatType x, FloatType base) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(base) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(base) ?
			base :
		bksge::isinf(x) ?
			x :
		base == 0 ?
			x :
		round_up_unchecked(x, base);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ROUND_UP_IMPL_HPP
