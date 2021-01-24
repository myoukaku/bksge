/**
 *	@file	cos_inl.hpp
 *
 *	@brief	cos 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_COS_INL_HPP
#define BKSGE_FND_CMATH_INL_COS_INL_HPP

#include <bksge/fnd/cmath/cos.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)

inline BKSGE_CONSTEXPR float
cos_unchecked(float x) BKSGE_NOEXCEPT
{
	return __builtin_cosf(x);
}

inline BKSGE_CONSTEXPR double
cos_unchecked(double x) BKSGE_NOEXCEPT
{
	return __builtin_cos(x);
}

inline BKSGE_CONSTEXPR long double
cos_unchecked(long double x) BKSGE_NOEXCEPT
{
	return __builtin_cosl(x);
}

#else

template <typename T>
inline BKSGE_CONSTEXPR T
cos_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::cos(x);
}

#endif

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
cos_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::iszero(x) ?
			FloatType(1) :
		bksge::isinf(x) || bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		cos_unchecked(x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType>
cos(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::cos_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_COS_INL_HPP
