/**
 *	@file	conjunction_inl.hpp
 *
 *	@brief	conjunction の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INL_CONJUNCTION_INL_HPP
#define BKSGE_FND_TYPE_TRAITS_INL_CONJUNCTION_INL_HPP

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <typename...>
struct conjunction_impl;

template <>
struct conjunction_impl<>
	: public std::true_type
{};

template <typename B0>
struct conjunction_impl<B0>
	: public B0
{};

template <typename B0, typename... Bn>
struct conjunction_impl<B0, Bn...>
	: public std::conditional<
		static_cast<bool>(B0::value),
		conjunction_impl<Bn...>,
		B0
	>::type
{};

}	// namespace detail

template <typename... B>
struct conjunction
	: public detail::conjunction_impl<B...>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_INL_CONJUNCTION_INL_HPP
