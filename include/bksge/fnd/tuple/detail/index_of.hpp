﻿/**
 *	@file	index_of.hpp
 *
 *	@brief	index_of の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_INDEX_OF_HPP
#define BKSGE_FND_TUPLE_DETAIL_INDEX_OF_HPP

#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <cstddef>

namespace bksge
{

namespace tuple_detail
{

// Returns the first appearance of T in Types.
// Returns sizeof...(Types) if T is not in Types.
template <typename T, typename... Types>
struct index_of
	: public bksge::integral_constant<std::size_t, 0> {};

template <typename T, typename First, typename... Rest>
struct index_of<T, First, Rest...>
	: public bksge::integral_constant<std::size_t,
		bksge::is_same<T, First>::value ? 0 : index_of<T, Rest...>::value + 1> {};

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_INDEX_OF_HPP
