/**
 *	@file	isnan_inl.hpp
 *
 *	@brief	isnan 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ISNAN_INL_HPP
#define BKSGE_FND_CMATH_INL_ISNAN_INL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isnan_impl(FloatType x) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isnan(x);
#else
	return !(x == x);
#endif
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bool
isnan(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::isnan_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ISNAN_INL_HPP
