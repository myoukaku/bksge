/**
 *	@file	rsqrt_impl.hpp
 *
 *	@brief	rsqrt 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RSQRT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_RSQRT_IMPL_HPP

#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
rsqrt_unchecked(T x) BKSGE_NOEXCEPT
{
	return T(1) / bksge::detail::sqrt_unchecked(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
rsqrt_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		x < 0 ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) ?
			FloatType(0) :
		bksge::iszero(x) ?
			std::numeric_limits<FloatType>::infinity() :
		rsqrt_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RSQRT_IMPL_HPP
