/**
 *	@file	is_nothrow_invocable_r_inl.hpp
 *
 *	@brief	is_nothrow_invocable_r の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_INVOCABLE_R_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_INVOCABLE_R_INL_HPP

#include <bksge/fnd/type_traits/is_nothrow_invocable_r.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4244)

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r
	: public detail::constant_wrapper<
		std::is_nothrow_invocable_r<R, Fn, ArgTypes...>
	>
{};

BKSGE_WARNING_POP()

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)
#include <bksge/fnd/type_traits/inl/is_invocable_r_inl.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <utility>
#else
#include <bksge/fnd/type_traits/is_invocable_r.hpp>
#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX11_NOEXCEPT)

namespace detail
{

template <bool, typename... Types>
struct is_nothrow_invocable_impl_2
	: public bksge::false_type
{};

template <typename... Types>
struct is_nothrow_invocable_impl_2<true, Types...>
	: public bksge::bool_constant<
		noexcept(bksge::invoke(std::declval<Types>()...))
	>
{};

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_impl
{
	using Result = bksge::invoke_result<Fn, ArgTypes...>;

	using type = typename is_nothrow_invocable_impl_2<
		detail::is_invocable_impl<Result, R>::value,
		Fn, ArgTypes...
	>::type;
};

}	// namespace detail

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r
	: public detail::is_nothrow_invocable_impl<R, Fn, ArgTypes...>::type
{};

#else

template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r
	: public bksge::is_invocable_r<R, Fn, ArgTypes...>
{};

#endif

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_INVOCABLE_R_INL_HPP
