/**
 *	@file	radians_to_degrees_impl.hpp
 *
 *	@brief	radians_to_degrees 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RADIANS_TO_DEGREES_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_RADIANS_TO_DEGREES_IMPL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
radians_to_degrees_unchecked(T x) BKSGE_NOEXCEPT
{
	return x * 180 / bksge::pi_t<T>();
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
radians_to_degrees_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) ?
			x :
		radians_to_degrees_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RADIANS_TO_DEGREES_IMPL_HPP
