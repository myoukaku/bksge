/**
 *	@file	cmp_less.hpp
 *
 *	@brief	cmp_less を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_CMP_LESS_HPP
#define BKSGE_FND_UTILITY_CMP_LESS_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace bksge
{

using std::cmp_less;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/is_signed.hpp>
#include <bksge/fnd/type_traits/make_unsigned.hpp>
#include <bksge/fnd/type_traits/detail/is_standard_integer.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T, typename U,
	bool = bksge::is_signed<T>::value,
	bool = bksge::is_signed<U>::value
>
struct cmp_less_impl
{
	static BKSGE_CONSTEXPR bool
	invoke(T t, U u) BKSGE_NOEXCEPT
	{
		return t < u;
	}
};

template <typename T, typename U>
struct cmp_less_impl<T, U, true, false>
{
	static BKSGE_CONSTEXPR bool
	invoke(T t, U u) BKSGE_NOEXCEPT
	{
		return t < 0 || bksge::make_unsigned_t<T>(t) < u;
	}
};

template <typename T, typename U>
struct cmp_less_impl<T, U, false, true>
{
	static BKSGE_CONSTEXPR bool
	invoke(T t, U u) BKSGE_NOEXCEPT
	{
		return u >= 0 && t < bksge::make_unsigned_t<U>(u);
	}
};

}	// namespace detail

template <typename T, typename U>
inline BKSGE_CONSTEXPR bool
cmp_less(T t, U u) BKSGE_NOEXCEPT
{
	static_assert(bksge::detail::is_standard_integer<T>::value, "");
	static_assert(bksge::detail::is_standard_integer<U>::value, "");

	return detail::cmp_less_impl<T, U>::invoke(t, u);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_UTILITY_CMP_LESS_HPP
