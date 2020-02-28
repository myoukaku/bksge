/**
 *	@file	my_tuple.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_TUPLE_MY_TUPLE_HPP
#define UNIT_TEST_FND_TUPLE_MY_TUPLE_HPP

#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <tuple>

namespace bksge_tuple_test
{

template <typename... Types>
struct MyTuple
{
};

}	// namespace bksge_tuple_test

namespace std
{

template <bksge::size_t I, typename... Types>
struct tuple_element<I, bksge_tuple_test::MyTuple<Types...>>
{
public:
	static_assert(I < sizeof...(Types), "tuple_element index out of range");
	using type = bksge::nth_t<I, Types...>;
};

}	// namespace std

#endif // UNIT_TEST_FND_TUPLE_MY_TUPLE_HPP
