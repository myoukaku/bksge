/**
 *	@file	is_odd_inl.hpp
 *
 *	@brief	is_odd 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_IS_ODD_INL_HPP
#define BKSGE_FND_CMATH_INL_IS_ODD_INL_HPP

#include <bksge/fnd/cmath/is_odd.hpp>
#include <bksge/fnd/cmath/fmod.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
is_odd_impl(FloatType x) BKSGE_NOEXCEPT
{
	return bksge::fmod(bksge::fabs(x), FloatType(2)) == FloatType(1);
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR bool
is_odd(ArithmeticType x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<ArithmeticType>;
	return detail::is_odd_impl(static_cast<type>(x));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_IS_ODD_INL_HPP
