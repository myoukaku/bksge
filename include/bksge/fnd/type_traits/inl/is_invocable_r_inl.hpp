/**
 *	@file	is_invocable_r_inl.hpp
 *
 *	@brief	is_invocable_r の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_INVOCABLE_R_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_INVOCABLE_R_INL_HPP

#include <bksge/fnd/type_traits/is_invocable_r.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename R, typename Fn, typename... ArgTypes>
struct is_invocable_r
	: public detail::constant_wrapper<
		std::is_invocable_r<R, Fn, ArgTypes...>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>

namespace bksge
{

namespace detail
{

template <typename Result, typename Ret, typename = bksge::void_t<>>
struct is_invocable_impl
	: public bksge::false_type
{};

template <typename Result, typename Ret>
struct is_invocable_impl<Result, Ret, bksge::void_t<typename Result::type>>
	: public bksge::disjunction<
		bksge::is_void<Ret>,
		bksge::is_convertible<typename Result::type, Ret>
	>::type
{};

}	// namespace detail

template <typename R, typename Fn, typename... ArgTypes>
struct is_invocable_r
	: public detail::is_invocable_impl<
		bksge::invoke_result<Fn, ArgTypes...>, R
	>::type
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_INVOCABLE_R_INL_HPP
