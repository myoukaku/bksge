/**
 *	@file	get.hpp
 *
 *	@brief	get の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_GET_HPP
#define BKSGE_FND_TUPLE_GET_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE) && defined(__cpp_lib_tuples_by_type) && (__cpp_lib_tuples_by_type >= 201304)

namespace bksge
{

//using std::get;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/detail/get_helper.hpp>
#include <bksge/fnd/tuple/detail/index_of.hpp>
#include <bksge/fnd/tuple/detail/exactly_once.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR bksge::tuple_element_t<I, tuple<Types...>>&
get(tuple<Types...>& t) BKSGE_NOEXCEPT
{
	return tuple_detail::get_helper<I>(t);
}

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR bksge::tuple_element_t<I, tuple<Types...>> const&
get(tuple<Types...> const& t) BKSGE_NOEXCEPT
{
	return tuple_detail::get_helper<I>(t);
}

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR bksge::tuple_element_t<I, tuple<Types...>>&&
get(tuple<Types...>&& t) BKSGE_NOEXCEPT
{
	using element_type = bksge::tuple_element_t<I, tuple<Types...>>;
	return bksge::forward<element_type&&>(bksge::get<I>(t));
}

template <std::size_t I, typename... Types>
BKSGE_CONSTEXPR bksge::tuple_element_t<I, tuple<Types...>> const&&
get(tuple<Types...> const&& t) BKSGE_NOEXCEPT
{
	using element_type = bksge::tuple_element_t<I, tuple<Types...>>;
	return bksge::forward<element_type const&&>(bksge::get<I>(t));
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T&
get(tuple<Types...>& t) BKSGE_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "");
	return bksge::get<tuple_detail::index_of<T, Types...>::value>(t);
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T&&
get(tuple<Types...>&& t) BKSGE_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "");
	return bksge::get<tuple_detail::index_of<T, Types...>::value>(bksge::move(t));
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T const&
get(tuple<Types...> const& t) BKSGE_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "");
	return bksge::get<tuple_detail::index_of<T, Types...>::value>(t);
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T const&&
get(tuple<Types...> const&& t) BKSGE_NOEXCEPT
{
	static_assert(tuple_detail::exactly_once<T, Types...>::value, "");
	return bksge::get<tuple_detail::index_of<T, Types...>::value>(bksge::move(t));
}

}	// namespace bksge

#include <bksge/fnd/tuple/tuple.hpp>

#endif

#endif // BKSGE_FND_TUPLE_GET_HPP
