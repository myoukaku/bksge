/**
 *	@file	rsqrt_inl.hpp
 *
 *	@brief	rsqrt 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_RSQRT_INL_HPP
#define BKSGE_FND_CMATH_INL_RSQRT_INL_HPP

#include <bksge/fnd/cmath/rsqrt.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <limits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
rsqrt_unchecked(T x) BKSGE_NOEXCEPT
{
	return T(1) / bksge::cmath::detail::sqrt_unchecked(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
rsqrt_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		x < 0 ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::isinf(x) ?
			FloatType(0) :
		bksge::iszero(x) ?
			std::numeric_limits<FloatType>::infinity() :
		bksge::isnan(x) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		rsqrt_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
rsqrt(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::rsqrt_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_RSQRT_INL_HPP
