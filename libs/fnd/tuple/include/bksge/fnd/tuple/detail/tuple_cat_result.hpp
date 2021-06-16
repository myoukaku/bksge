/**
 *	@file	tuple_cat_result.hpp
 *
 *	@brief	tuple_cat_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_TUPLE_CAT_RESULT_HPP
#define BKSGE_FND_TUPLE_DETAIL_TUPLE_CAT_RESULT_HPP

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace tuple_detail
{

template <typename Tuple,
	typename = bksge::make_index_sequence<bksge::tuple_size<Tuple>::value>>
struct to_tuple;

template <typename Tuple, bksge::size_t... Indices>
struct to_tuple<Tuple, bksge::index_sequence<Indices...>>
{
	using type = bksge::tuple<bksge::tuple_element_t<Indices, Tuple>...>;
};

// Returns the bksge::tuple equivalent of a tuple-like type.
template <typename Tuple>
using to_tuple_t = typename to_tuple<bksge::remove_cvref_t<Tuple>>::type;

// Combines several bksge::tuple's into a single one.
template <typename...>
struct combine_tuples;

template <>
struct combine_tuples<>
{
	using type = bksge::tuple<>;
};

template <typename... Types>
struct combine_tuples<bksge::tuple<Types...>>
{
	using type = bksge::tuple<Types...>;
};

template <typename... Types1, typename... Types2, typename... Rem>
struct combine_tuples<bksge::tuple<Types1...>, bksge::tuple<Types2...>, Rem...>
	: public combine_tuples<bksge::tuple<Types1..., Types2...>, Rem...>
{};

// Computes the result type of tuple_cat given a set of tuple-like types.
template <typename... Tuples>
struct tuple_cat_result
	: public combine_tuples<to_tuple_t<Tuples>...>
{};

template <typename... Tuples>
using tuple_cat_result_t = typename tuple_cat_result<Tuples...>::type;

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_TUPLE_CAT_RESULT_HPP
