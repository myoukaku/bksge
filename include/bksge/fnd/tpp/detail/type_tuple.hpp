﻿/**
 *	@file	type_tuple.hpp
 *
 *	@brief	type_tuple の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TPP_DETAIL_TYPE_TUPLE_HPP
#define BKSGE_FND_TPP_DETAIL_TYPE_TUPLE_HPP

#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/index_sequence_for.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tpp
{

namespace detail
{

template <bksge::size_t I, typename T>
struct element_holder
{
public:
	T m_value;

	BKSGE_CONSTEXPR element_holder(T&& value)
		: m_value(bksge::forward<T>(value))
	{}

private:
	element_holder& operator=(element_holder const&) { return *this; }
};

template <typename IndexSequence, typename... Types>
class type_tuple_impl;

template <bksge::size_t... Indices, typename... Types>
class type_tuple_impl<bksge::index_sequence<Indices...>, Types...>
	: public element_holder<Indices, Types>...
{
public:
	BKSGE_CONSTEXPR type_tuple_impl(Types&&... args)
		: element_holder<Indices, Types>(bksge::forward<Types>(args))...
	{}

private:
	type_tuple_impl& operator=(type_tuple_impl const&) { return *this; }
};

template <typename... Types>
using type_tuple =
	type_tuple_impl<bksge::index_sequence_for<Types...>, Types...>;

template <bksge::size_t N, typename T>
static BKSGE_CONSTEXPR element_holder<N, T> const&
select(element_holder<N, T> const& t)
{
	return t;
}

}	// namespace detail

}	// namespace tpp

}	// namespace bksge

#endif // BKSGE_FND_TPP_DETAIL_TYPE_TUPLE_HPP
