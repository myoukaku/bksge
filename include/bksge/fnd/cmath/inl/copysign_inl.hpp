/**
 *	@file	copysign_inl.hpp
 *
 *	@brief	copysign 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_COPYSIGN_INL_HPP
#define BKSGE_FND_CMATH_INL_COPYSIGN_INL_HPP

#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
copysign_impl(float x, float y) BKSGE_NOEXCEPT
{
	return __builtin_copysignf(x, y);
}

inline BKSGE_CONSTEXPR double
copysign_impl(double x, double y) BKSGE_NOEXCEPT
{
	return __builtin_copysign(x, y);
}

inline BKSGE_CONSTEXPR long double
copysign_impl(long double x, long double y) BKSGE_NOEXCEPT
{
	return __builtin_copysignl(x, y);
}

#else

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
copysign_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(y) || bksge::isnan(y) ?
			x :
		bksge::signbit(x) != bksge::signbit(y) ?
			-x :
		x;
}

#endif

}	// namespace detail

template <typename ArithmeticType1, typename ArithmeticType2, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
copysign(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType1, ArithmeticType2>;
	return detail::copysign_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_COPYSIGN_INL_HPP
