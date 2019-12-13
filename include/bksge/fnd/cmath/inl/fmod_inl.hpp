/**
 *	@file	fmod_inl.hpp
 *
 *	@brief	fmod 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_FMOD_INL_HPP
#define BKSGE_FND_CMATH_INL_FMOD_INL_HPP

#include <bksge/fnd/cmath/fmod.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/trunc.hpp>
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

#endif // BKSGE_FND_CMATH_INL_FMOD_INL_HPP
