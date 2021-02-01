/**
 *	@file	degrees_to_radians_impl.hpp
 *
 *	@brief	degrees_to_radians 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_DEGREES_TO_RADIANS_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_DEGREES_TO_RADIANS_IMPL_HPP

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
degrees_to_radians_unchecked(T x) BKSGE_NOEXCEPT
{
	return x * bksge::pi_t<T>() / 180;
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
degrees_to_radians_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isinf(x) || bksge::isnan(x) ?
			x :
		degrees_to_radians_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_DEGREES_TO_RADIANS_IMPL_HPP
