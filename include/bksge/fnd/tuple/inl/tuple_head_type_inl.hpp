/**
 *	@file	tuple_head_type_inl.hpp
 *
 *	@brief	tuple_head_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_HEAD_TYPE_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_HEAD_TYPE_INL_HPP

#include <bksge/fnd/tuple/tuple_head_type.hpp>

namespace bksge
{

template <typename Tuple>
struct tuple_head_type<Tuple const> : public tuple_head_type<Tuple> {};

template <typename Tuple>
struct tuple_head_type<Tuple volatile> : public tuple_head_type<Tuple> {};

template <typename Tuple>
struct tuple_head_type<Tuple const volatile> : public tuple_head_type<Tuple> {};

template <template <typename...> class Tuple, typename Head, typename... Tail>
struct tuple_head_type<Tuple<Head, Tail...>>
{
	using type = Head;
};

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_HEAD_TYPE_INL_HPP
