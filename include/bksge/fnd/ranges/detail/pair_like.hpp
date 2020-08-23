﻿/**
 *	@file	pair_like.hpp
 *
 *	@brief	pair_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_HPP
#define BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_HPP

#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <tuple>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept pair_like =
	!bksge::is_reference<T>::value &&
	requires(T t)
	{
		typename std::tuple_size<T>::type;
		requires bksge::derived_from<std::tuple_size<T>, std::integral_constant<std::size_t, 2>>;
		typename bksge::tuple_element_t<0, bksge::remove_const_t<T>>;
		typename bksge::tuple_element_t<1, bksge::remove_const_t<T>>;
		{ std::get<0>(t) } -> bksge::convertible_to<const bksge::tuple_element_t<0, T>&>;
		{ std::get<1>(t) } -> bksge::convertible_to<const bksge::tuple_element_t<1, T>&>;
	};

#else

template <typename T>
struct pair_like_impl
{
private:
	template <typename U,
		typename = typename std::tuple_size<U>::type,
		typename = bksge::tuple_element_t<0, bksge::remove_const_t<U>>,
		typename = bksge::tuple_element_t<1, bksge::remove_const_t<U>>
	>
	static auto test(int) -> bksge::conjunction<
		bksge::derived_from<std::tuple_size<U>, std::integral_constant<std::size_t, 2>>,
		bksge::convertible_to<decltype(std::get<0>(bksge::declval<U>())), const bksge::tuple_element_t<0, U>&>,
		bksge::convertible_to<decltype(std::get<1>(bksge::declval<U>())), const bksge::tuple_element_t<1, U>&>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using pair_like = typename pair_like_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_PAIR_LIKE_HPP