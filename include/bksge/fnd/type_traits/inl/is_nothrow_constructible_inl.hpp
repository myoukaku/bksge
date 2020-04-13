/**
 *	@file	is_nothrow_constructible_inl.hpp
 *
 *	@brief	is_nothrow_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_CONSTRUCTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_STDLIB_DINKUMWARE)

#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/detail/is_constructible_helper.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace detail
{

#if (defined(_MSC_VER) && (_MSC_VER >= 1500)) || \
	BKSGE_HAS_FEATURE(is_constructible)

// is_nothrow_constructible
template <typename T, typename... Args>
struct is_nothrow_constructible
	: public bksge::bool_constant<
		__is_nothrow_constructible(T, Args...)
	>
{};

#elif defined(BKSGE_HAS_CXX11_NOEXCEPT)

// is_nothrow_constructible_impl
template <bool, typename T, typename... Args>
struct is_nothrow_constructible_impl
	: public bksge::false_type
{};

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4197)	// キャストの トップレベルの volatile は無視されます。

template <typename T, typename... Args>
struct is_nothrow_constructible_impl<true, T, Args...>
	: public bksge::bool_constant<
		noexcept(T(bksge::declval<Args>()...))
	>
{};


template <typename T, typename Arg>
struct is_nothrow_constructible_impl<true, T, Arg>
	: public bksge::bool_constant<
		noexcept(static_cast<T>(bksge::declval<Arg>()))
	>
{};

BKSGE_WARNING_POP()

// is_nothrow_constructible
template <typename T, typename... Args>
struct is_nothrow_constructible
	: public is_nothrow_constructible_impl<
		bksge::is_constructible<T, Args...>::value,
		T, Args...
	>
{};

#else

// is_nothrow_constructible
template <typename T, typename... Args>
struct is_nothrow_constructible
	: public bksge::false_type
{};

#endif

}	// namespace detail

// is_nothrow_constructible
template <typename T, typename... Args>
struct is_nothrow_constructible
	: public detail::is_constructible_helper<
		detail::is_nothrow_constructible, T, Args...
	>
{};

}	// namespace bksge

#elif defined(BKSGE_STDLIB_LIBSTDCPP3)

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/type_traits/is_unbounded_array.hpp>
#include <type_traits>

namespace bksge
{

template <typename T, typename... Args>
struct is_nothrow_constructible
	: public bksge::bool_constant<
		!bksge::is_unbounded_array<T>::value &&
		!bksge::is_function<T>::value &&
		std::is_nothrow_constructible<T, Args...>::value
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

template <typename T, typename... Args>
struct is_nothrow_constructible
	: public detail::constant_wrapper<
		std::is_nothrow_constructible<T, Args...>
	>
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_CONSTRUCTIBLE_INL_HPP
