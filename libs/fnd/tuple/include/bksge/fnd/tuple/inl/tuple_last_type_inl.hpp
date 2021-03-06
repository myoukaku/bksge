﻿/**
 *	@file	tuple_last_type_inl.hpp
 *
 *	@brief	tuple_last_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_LAST_TYPE_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_LAST_TYPE_INL_HPP

#include <bksge/fnd/tuple/tuple_last_type.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace detail
{

// tuple_last_type_impl
template <typename Tuple, bksge::size_t N>
struct tuple_last_type_impl
{
	using type =
		bksge::tuple_element_t<N - 1, Tuple>;
};

template <typename Tuple>
struct tuple_last_type_impl<Tuple, 0>
{
};

}	// namespace detail

// tuple_last_type
template <
	template <typename...> class Tuple,
	typename... Types
>
struct tuple_last_type<Tuple<Types...>>
	: public detail::tuple_last_type_impl<
		Tuple<Types...>, sizeof...(Types)
	>
{};

template <typename Tuple>
struct tuple_last_type<Tuple const>
	: public tuple_last_type<Tuple> {};

template <typename Tuple>
struct tuple_last_type<Tuple volatile>
	: public tuple_last_type<Tuple> {};

template <typename Tuple>
struct tuple_last_type<Tuple const volatile>
	: public tuple_last_type<Tuple> {};

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_LAST_TYPE_INL_HPP
