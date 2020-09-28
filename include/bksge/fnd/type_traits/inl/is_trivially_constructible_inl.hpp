/**
 *	@file	is_trivially_constructible_inl.hpp
 *
 *	@brief	is_trivially_constructible の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_CONSTRUCTIBLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_CONSTRUCTIBLE_INL_HPP

#include <bksge/fnd/type_traits/is_trivially_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/detail/is_constructible_helper.hpp>
#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if (defined(BKSGE_MSVC) && (BKSGE_MSVC >= 1500)) || \
	BKSGE_HAS_FEATURE(is_trivially_constructible)

template <bool, typename T, typename... Args>
struct is_trivially_constructible_impl
	: public bksge::bool_constant<__is_trivially_constructible(T, Args...)>
{};

#else

template <bool, typename T, typename... Args>
struct is_trivially_constructible_impl
	: public detail::constant_wrapper<
		std::is_trivially_constructible<T, Args...>
	>
{};

#endif

template <typename T, typename... Args>
struct is_trivially_constructible_impl<false, T, Args...>
	: public bksge::false_type
{};

template <typename T, typename... Args>
struct is_trivially_constructible
	: public is_trivially_constructible_impl<
		bksge::is_trivially_destructible<T>::value,
		T, Args...
	>
{};

}	// namespace detail

template <typename T, typename... Args>
struct is_trivially_constructible
	: public detail::is_constructible_helper<
		detail::is_trivially_constructible, T, Args...
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_TRIVIALLY_CONSTRUCTIBLE_INL_HPP
