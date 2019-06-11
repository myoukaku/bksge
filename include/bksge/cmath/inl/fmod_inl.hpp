/**
 *	@file	fmod_inl.hpp
 *
 *	@brief	fmod 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_FMOD_INL_HPP
#define BKSGE_CMATH_INL_FMOD_INL_HPP

#include <bksge/cmath/fmod.hpp>
#include <bksge/cmath/isnan.hpp>
#include <bksge/cmath/isinf.hpp>
#include <bksge/cmath/iszero.hpp>
#include <bksge/cmath/trunc.hpp>
#include <bksge/type_traits/float_promote.hpp>
#include <limits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
fmod_unchecked(T x, T y) BKSGE_NOEXCEPT
{
	return x - (bksge::trunc(x / y) * y);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
fmod_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isnan(y) || bksge::isinf(x) || bksge::iszero(y) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		bksge::iszero(x) || bksge::isinf(y) ?
			x :
		fmod_unchecked(x, y);
}

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
fmod(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType1, ArithmeticType2>;
	return detail::fmod_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_FMOD_INL_HPP
