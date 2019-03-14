/**
 *	@file	iszero_inl.hpp
 *
 *	@brief	iszero 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_INL_ISZERO_INL_HPP
#define BKSGE_CMATH_INL_ISZERO_INL_HPP

#include <bksge/cmath/iszero.hpp>
#include <bksge/type_traits/float_promote.hpp>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
iszero_impl(FloatType x) BKSGE_NOEXCEPT
{
	return x == FloatType(0);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bool
iszero(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::iszero_impl(static_cast<type>(x));
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_CMATH_INL_ISZERO_INL_HPP
