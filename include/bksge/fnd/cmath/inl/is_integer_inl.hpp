/**
 *	@file	is_integer_inl.hpp
 *
 *	@brief	is_integer 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_IS_INTEGER_INL_HPP
#define BKSGE_FND_CMATH_INL_IS_INTEGER_INL_HPP

#include <bksge/fnd/cmath/is_integer.hpp>
#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/trunc.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
is_integer_impl(FloatType x) BKSGE_NOEXCEPT
{
	return bksge::isfinite(x) && (bksge::trunc(x) == x);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bool
is_integer(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::is_integer_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_IS_INTEGER_INL_HPP
