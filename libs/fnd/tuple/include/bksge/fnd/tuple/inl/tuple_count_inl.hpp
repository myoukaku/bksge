/**
 *	@file	tuple_count_inl.hpp
 *
 *	@brief	tuple_count の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_COUNT_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_COUNT_INL_HPP

#include <bksge/fnd/tuple/tuple_count.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <cstddef>

namespace bksge
{

template <typename T, typename Tuple>
struct tuple_count
	: public bksge::integral_constant<std::size_t, 0>
{};

template <typename T, template <typename...> class Tuple, typename Head, typename... Tail>
struct tuple_count<T, Tuple<Head, Tail...>>
	: public bksge::integral_constant<std::size_t,
		(bksge::is_same<T, Head>::value ? 1 : 0) +
		tuple_count<T, Tuple<Tail...>>::value
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_COUNT_INL_HPP
