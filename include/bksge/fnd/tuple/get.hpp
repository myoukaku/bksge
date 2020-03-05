/**
 *	@file	get.hpp
 *
 *	@brief	get 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_GET_HPP
#define BKSGE_FND_TUPLE_GET_HPP

#include <tuple>

namespace bksge
{

using std::get;

}	// namespace bksge

#include <bksge/fnd/config.hpp>

#if !(BKSGE_CXX_STANDARD >= 14 && defined(__cpp_lib_tuples_by_type) && (__cpp_lib_tuples_by_type >= 201304))

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/detail/find_detail.hpp>
#include <bksge/fnd/utility/move.hpp>

namespace bksge
{

template <typename T, typename... Types>
inline BKSGE_CXX14_CONSTEXPR T&
get(tuple<Types...>& t) BKSGE_NOEXCEPT
{
	return bksge::get<find_detail::find_exactly_one_t<T, Types...>::value>(t);
}

template <typename T, typename... Types>
inline BKSGE_CXX14_CONSTEXPR T const&
get(tuple<Types...> const& t) BKSGE_NOEXCEPT
{
	return bksge::get<find_detail::find_exactly_one_t<T, Types...>::value>(t);
}

template <typename T, typename... Types>
inline BKSGE_CXX14_CONSTEXPR T&&
get(tuple<Types...>&& t) BKSGE_NOEXCEPT
{
	return bksge::get<find_detail::find_exactly_one_t<T, Types...>::value>(bksge::move(t));
}

template <typename T, typename... Types>
inline BKSGE_CXX14_CONSTEXPR T const&&
get(tuple<Types...> const&& t) BKSGE_NOEXCEPT
{
	return bksge::get<find_detail::find_exactly_one_t<T, Types...>::value>(bksge::move(t));
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_TUPLE_GET_HPP
