/**
 *	@file	abs_inl.hpp
 *
 *	@brief	abs 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_INL_ABS_INL_HPP
#define BKSGE_FND_CMATH_INL_ABS_INL_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
abs_impl(T x, bksge::enable_if_t<std::is_unsigned<T>::value>* = nullptr) BKSGE_NOEXCEPT
{
	return x;
}

template <typename T>
inline BKSGE_CONSTEXPR T
abs_impl(T x, bksge::enable_if_t<!std::is_unsigned<T>::value>* = nullptr) BKSGE_NOEXCEPT
{
	return x < 0 ? -x : x;
}

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR ArithmeticType
abs(ArithmeticType x) BKSGE_NOEXCEPT
{
	return detail::abs_impl(x);
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ABS_INL_HPP
