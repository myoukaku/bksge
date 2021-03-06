﻿/**
 *	@file	is_nothrow_invocable_inl.hpp
 *
 *	@brief	is_nothrow_invocable の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_INVOCABLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_INVOCABLE_INL_HPP

#include <bksge/fnd/type_traits/is_nothrow_invocable.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_invocable) && (__cpp_lib_is_invocable >= 201703)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename Fn, typename... ArgTypes>
struct is_nothrow_invocable
	: public detail::constant_wrapper<
		std::is_nothrow_invocable<Fn, ArgTypes...>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/is_nothrow_invocable_r.hpp>

namespace bksge
{

template <typename Fn, typename... ArgTypes>
struct is_nothrow_invocable
	: public bksge::is_nothrow_invocable_r<void, Fn, ArgTypes...>
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_INVOCABLE_INL_HPP
