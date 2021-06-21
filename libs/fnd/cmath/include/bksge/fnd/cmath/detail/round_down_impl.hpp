/**
 *	@file	round_down_impl.hpp
 *
 *	@brief	round_down 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ROUND_DOWN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ROUND_DOWN_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
round_down_unchecked(T x, T base) BKSGE_NOEXCEPT
{
	return bksge::floor(x / base) * base;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
round_down_impl(FloatType x, FloatType base) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(base) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(base) ?
			base :
		bksge::isinf(x) ?
			x :
		base == 0 ?
			x :
		round_down_unchecked(x, base);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ROUND_DOWN_IMPL_HPP
