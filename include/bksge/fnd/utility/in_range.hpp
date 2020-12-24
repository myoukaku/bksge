/**
 *	@file	in_range.hpp
 *
 *	@brief	in_range を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_IN_RANGE_HPP
#define BKSGE_FND_UTILITY_IN_RANGE_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace bksge
{

using std::in_range;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/is_signed.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/type_traits/detail/is_standard_integer.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename U, typename T,
	bool = bksge::is_signed<U>::value,
	bool = bksge::is_signed<T>::value
>
struct in_range_impl
{
	static BKSGE_CONSTEXPR bool
	invoke(T t) BKSGE_NOEXCEPT
	{
		return bksge::numeric_limits<U>::min() <= t && t <= bksge::numeric_limits<U>::max();
	}
};

template <typename U, typename T>
struct in_range_impl<U, T, false, true>
{
	static BKSGE_CONSTEXPR bool
	invoke(T t) BKSGE_NOEXCEPT
	{
		return t >= 0 && bksge::make_unsigned_t<T>(t) <= bksge::numeric_limits<U>::max();
	}
};

template <typename U, typename T>
struct in_range_impl<U, T, true, false>
{
	static BKSGE_CONSTEXPR bool
	invoke(T t) BKSGE_NOEXCEPT
	{
		return t <= bksge::make_unsigned_t<U>(bksge::numeric_limits<U>::max());
	}
};

}	// namespace detail

template <typename U, typename T>
inline BKSGE_CONSTEXPR bool
in_range(T t) BKSGE_NOEXCEPT
{
	static_assert(bksge::detail::is_standard_integer<U>::value, "");
	static_assert(bksge::detail::is_standard_integer<T>::value, "");

	return detail::in_range_impl<U, T>::invoke(t);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_IN_RANGE_HPP
