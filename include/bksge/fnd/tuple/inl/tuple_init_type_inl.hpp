/**
 *	@file	tuple_init_type_inl.hpp
 *
 *	@brief	tuple_init_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_INIT_TYPE_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_INIT_TYPE_INL_HPP

#include <bksge/fnd/tuple/tuple_init_type.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

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
	bksge::size_t... Indices>
struct tuple_init_type_impl_2<
	Tuple<Types...>,
	bksge::index_sequence<Indices...>>
{
	using type =
		Tuple<
			bksge::tuple_element_t<
				Indices, Tuple<Types...>
			>...
		>;
};

// tuple_init_type_impl
template <typename Tuple, bksge::size_t N>
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

#endif // BKSGE_FND_TUPLE_INL_TUPLE_INIT_TYPE_INL_HPP
