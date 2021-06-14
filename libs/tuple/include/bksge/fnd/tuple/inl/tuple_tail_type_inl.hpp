/**
 *	@file	tuple_tail_type_inl.hpp
 *
 *	@brief	tuple_tail_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_TAIL_TYPE_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_TAIL_TYPE_INL_HPP

#include <bksge/fnd/tuple/tuple_tail_type.hpp>

namespace bksge
{

template <typename Tuple>
struct tuple_tail_type
{
	using type = Tuple;
};

template <template <typename...> class Tuple, typename Head, typename... Tail>
struct tuple_tail_type<Tuple<Head, Tail...>>
{
	using type = Tuple<Tail...>;
};

template <typename Tuple>
struct tuple_tail_type<Tuple const> : public tuple_tail_type<Tuple> {};

template <typename Tuple>
struct tuple_tail_type<Tuple volatile> : public tuple_tail_type<Tuple> {};

template <typename Tuple>
struct tuple_tail_type<Tuple const volatile> : public tuple_tail_type<Tuple> {};

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_TAIL_TYPE_INL_HPP
