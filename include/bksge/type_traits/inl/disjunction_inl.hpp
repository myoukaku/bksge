/**
 *	@file	disjunction_inl.hpp
 *
 *	@brief	disjunction の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TYPE_TRAITS_INL_DISJUNCTION_INL_HPP
#define BKSGE_TYPE_TRAITS_INL_DISJUNCTION_INL_HPP

#include <bksge/type_traits/disjunction.hpp>
#include <type_traits>

namespace bksge
{

namespace detail
{

template <typename...>
struct disjunction_impl;

template <>
struct disjunction_impl<>
	: public std::false_type
{};

template <typename B0>
struct disjunction_impl<B0>
	: public B0
{};

template <typename B0, typename... Bn>
struct disjunction_impl<B0, Bn...>
	: public std::conditional<
		static_cast<bool>(B0::value),
		B0,
		disjunction_impl<Bn...>
	>::type
{};

}	// namespace detail

template <typename... B>
struct disjunction
	: public detail::disjunction_impl<B...>
{};

}	// namespace bksge

#endif // BKSGE_TYPE_TRAITS_INL_DISJUNCTION_INL_HPP
