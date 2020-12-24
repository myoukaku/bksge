/**
 *	@file	midpoint.hpp
 *
 *	@brief	midpoint の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_MIDPOINT_HPP
#define BKSGE_FND_NUMERIC_MIDPOINT_HPP

#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/is_integral.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4308);	// negative integral constant converted to unsigned type

// integral
template <typename T, typename = bksge::enable_if_t<bksge::is_integral<T>::value>>
inline BKSGE_CXX14_CONSTEXPR T
midpoint_impl(T a, T b, bksge::detail::overload_priority<1>) BKSGE_NOEXCEPT
{
	using U = bksge::make_unsigned_t<T>;

	int k = 1;
	U m = a;
	U M = b;
	if (a > b)
	{
		k = -1;
		m = b;
		M = a;
	}
	return static_cast<T>(a + k * T(U(M - m) / 2));
}

BKSGE_WARNING_POP();

// floating
template <typename T>
inline BKSGE_CXX14_CONSTEXPR T
midpoint_impl(T a, T b, bksge::detail::overload_priority<0>) BKSGE_NOEXCEPT
{
	constexpr T lo = bksge::numeric_limits<T>::min() * 2;
	constexpr T hi = bksge::numeric_limits<T>::max() / 2;
	const T abs_a = a < 0 ? -a : a;
	const T abs_b = b < 0 ? -b : b;

	if (abs_a <= hi && abs_b <= hi) /*[[likely]]*/	// TODO
	{
		return (a + b) / 2; // always correctly rounded
	}

	if (abs_a < lo) // not safe to halve a
	{
		return a + b/2;
	}

	if (abs_b < lo) // not safe to halve b
	{
		return a/2 + b;
	}

	return a/2 + b/2;	    // otherwise correctly rounded
}

}	// namespace detail

template <typename T>
inline BKSGE_CXX14_CONSTEXPR
bksge::enable_if_t<
	bksge::conjunction<
		bksge::is_arithmetic<T>,
		bksge::is_same<bksge::remove_cv_t<T>, T>,
		bksge::negation<bksge::is_same<T, bool>>
	>::value,
	T
>
midpoint(T a, T b) BKSGE_NOEXCEPT
{
	return detail::midpoint_impl(a, b, bksge::detail::overload_priority<1>{});
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bksge::enable_if_t<bksge::is_object<T>::value, T*>
midpoint(T* a, T* b) BKSGE_NOEXCEPT
{
	static_assert(sizeof(T) != 0, "type must be complete");
	return a  + (b - a) / 2;
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_MIDPOINT_HPP
