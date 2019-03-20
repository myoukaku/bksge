/**
 *	@file	arithmetic_promote_inl.hpp
 *
 *	@brief	arithmetic_promote の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_ARITHMETIC_PROMOTE_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_ARITHMETIC_PROMOTE_INL_HPP

#include <bksge/type_traits/arithmetic_promote.hpp>
#include <bksge/type_traits/type_identity.hpp>
#include <type_traits>
#include <utility>		// declval

namespace bksge
{

namespace detail
{

template <typename... T>
struct arithmetic_promote_impl;

template <typename T>
struct arithmetic_promote_impl<T>
	: public bksge::type_identity<T>
{
	static_assert(std::is_arithmetic<T>::value, "");
};

template <typename T, typename U>
struct arithmetic_promote_impl<T, U>
	: public std::decay<decltype(std::declval<T>() + std::declval<U>())>
{
	static_assert(std::is_arithmetic<T>::value, "");
};

template <typename T, typename U, typename... Tail>
struct arithmetic_promote_impl<T, U, Tail...>
	: public arithmetic_promote_impl<typename arithmetic_promote_impl<T, U>::type, Tail...>
{};

}	// namespace detail

template <typename... T>
struct arithmetic_promote
	: public detail::arithmetic_promote_impl<
		typename std::remove_cv<T>::type...
	>
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_ARITHMETIC_PROMOTE_INL_HPP
