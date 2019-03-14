/**
 *	@file	is_swappable_inl.hpp
 *
 *	@brief	is_swappable の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_IS_SWAPPABLE_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_IS_SWAPPABLE_INL_HPP

#include <bksge/type_traits/is_swappable.hpp>
#include <bksge/type_traits/is_swappable_with.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <typename T, bool>
struct is_swappable_impl
	: public bksge::is_swappable_with<T&, T&>
{};

template <typename T>
struct is_swappable_impl<T, true>
	: public std::false_type
{};

}	// namespace detail

template <typename T>
struct is_swappable
	: public detail::is_swappable_impl<T, std::is_void<T>::value>
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_IS_SWAPPABLE_INL_HPP
