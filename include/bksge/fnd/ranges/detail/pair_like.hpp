/**
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
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

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
		typename bksge::tuple_size<T>::type;
		requires bksge::derived_from<bksge::tuple_size<T>, bksge::integral_constant<std::size_t, 2>>;
		typename bksge::tuple_element_t<0, bksge::remove_const_t<T>>;
		typename bksge::tuple_element_t<1, bksge::remove_const_t<T>>;
		{ get<0>(t) } -> bksge::convertible_to<bksge::tuple_element_t<0, T> const&>;
		{ get<1>(t) } -> bksge::convertible_to<bksge::tuple_element_t<1, T> const&>;
	};

#else

template <typename T>
struct pair_like_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<!bksge::is_reference<T>::value>,
		typename = typename bksge::tuple_size<U>::type,
		typename = bksge::enable_if_t<bksge::derived_from<
			bksge::tuple_size<U>, bksge::integral_constant<std::size_t, 2>
		>::value>,
		typename = bksge::tuple_element_t<0, bksge::remove_const_t<U>>,
		typename = bksge::tuple_element_t<1, bksge::remove_const_t<U>>,
		typename E1 = decltype(get<0>(bksge::declval<U>())),
		typename E2 = decltype(get<1>(bksge::declval<U>()))
	>
	static auto test(int) -> bksge::conjunction<
		bksge::convertible_to<E1, bksge::tuple_element_t<0, U> const&>,
		bksge::convertible_to<E2, bksge::tuple_element_t<1, U> const&>
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
