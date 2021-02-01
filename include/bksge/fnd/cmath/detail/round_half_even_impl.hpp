/**
 *	@file	round_half_even_impl.hpp
 *
 *	@brief	round_half_even 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ROUND_HALF_EVEN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ROUND_HALF_EVEN_IMPL_HPP

#include <bksge/fnd/cmath/ceil.hpp>
#include <bksge/fnd/cmath/floor.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
round_half_even_unchecked(T x, T h = T(0.5)) BKSGE_NOEXCEPT
{
	return bksge::ceil((x - h) * h) + bksge::floor((x + h) * h);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
round_half_even_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) || bksge::iszero(x) ?
			x :
		round_half_even_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ROUND_HALF_EVEN_IMPL_HPP
