﻿/**
 *	@file	is_nothrow_swappable_inl.hpp
 *
 *	@brief	is_nothrow_swappable の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_SWAPPABLE_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_SWAPPABLE_INL_HPP

#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable_with.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>

namespace bksge
{

namespace detail
{

template <typename T, bool>
struct is_nothrow_swappable_impl
	: public bksge::is_nothrow_swappable_with<T&, T&>
{};

template <typename T>
struct is_nothrow_swappable_impl<T, true>
	: public bksge::false_type
{};

}	// namespace detail

template <typename T>
struct is_nothrow_swappable
	: public detail::is_nothrow_swappable_impl<
		T, bksge::is_void<T>::value
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_IS_NOTHROW_SWAPPABLE_INL_HPP
