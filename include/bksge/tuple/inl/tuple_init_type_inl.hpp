﻿/**
 *	@file	tuple_init_type_inl.hpp
 *
 *	@brief	tuple_init_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_TUPLE_INL_TUPLE_INIT_TYPE_INL_HPP
#define BKSGE_TUPLE_INL_TUPLE_INIT_TYPE_INL_HPP

#include <bksge/tuple/tuple_init_type.hpp>
#include <bksge/utility/make_index_sequence.hpp>
#include <cstddef>
#include <tuple>

namespace bksge
{

namespace detail
{

// tuple_init_type_impl_2
template <typename Tuple, typename Indices>
struct tuple_init_type_impl_2;

template <
	template <typename...> class Tuple,
	typename... Types,
	std::size_t... Indices>
struct tuple_init_type_impl_2<
	Tuple<Types...>,
	bksge::index_sequence<Indices...>>
{
	using type =
		Tuple<
			typename std::tuple_element<
				Indices, Tuple<Types...>
			>::type...
		>;
};

// tuple_init_type_impl
template <typename Tuple, std::size_t N>
struct tuple_init_type_impl
	: public tuple_init_type_impl_2<
		Tuple, bksge::make_index_sequence<N - 1>
	>
{};

template <typename Tuple>
struct tuple_init_type_impl<Tuple, 0>
{
	using type = Tuple;
};

}	// namespace detail

// tuple_init_type
template <
	template <typename...> class Tuple,
	typename... Types
>
struct tuple_init_type<Tuple<Types...>>
	: public detail::tuple_init_type_impl<
		Tuple<Types...>, sizeof...(Types)
	>
{};

template <typename Tuple>
struct tuple_init_type<Tuple const>
	: public tuple_init_type<Tuple> {};

template <typename Tuple>
struct tuple_init_type<Tuple volatile>
	: public tuple_init_type<Tuple> {};

template <typename Tuple>
struct tuple_init_type<Tuple const volatile>
	: public tuple_init_type<Tuple> {};

}	// namespace bksge

#endif // BKSGE_TUPLE_INL_TUPLE_INIT_TYPE_INL_HPP
