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
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

namespace detail
{

template <
	typename T,
	bool = std::is_floating_point<T>::value,
	bool = std::is_unsigned<T>::value
>
struct abs_impl;

template <typename T, bool IsUnsigned>
struct abs_impl<T, true, IsUnsigned>
{
	static BKSGE_CONSTEXPR T
	invoke(T x) BKSGE_NOEXCEPT
	{
		return bksge::fabs(x);
	}
};

template <typename T>
struct abs_impl<T, false, true>
{
	static BKSGE_CONSTEXPR T
	invoke(T x) BKSGE_NOEXCEPT
	{
		return x;
	}
};

template <typename T>
struct abs_impl<T, false, false>
{
	static BKSGE_CONSTEXPR T
	invoke(T x) BKSGE_NOEXCEPT
	{
		return x < 0 ? -x : x;
	}
};

}	// namespace detail

template <typename ArithmeticType, typename>
inline BKSGE_CONSTEXPR ArithmeticType
abs(ArithmeticType x) BKSGE_NOEXCEPT
{
	return detail::abs_impl<ArithmeticType>::invoke(x);
}

}	// namespace cmath

}	// namespace bksge

#endif // BKSGE_FND_CMATH_INL_ABS_INL_HPP
