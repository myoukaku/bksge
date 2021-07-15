/**
 *	@file	get_helper.hpp
 *
 *	@brief	get_helper の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_GET_HELPER_HPP
#define BKSGE_FND_TUPLE_DETAIL_GET_HELPER_HPP

#include <bksge/fnd/tuple/detail/tuple_impl.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace tuple_detail
{

template <std::size_t I, typename Head, typename... Tail>
inline BKSGE_CONSTEXPR Head&
get_helper(tuple_impl<I, Head, Tail...>& t) BKSGE_NOEXCEPT
{
	return tuple_impl<I, Head, Tail...>::head(t);
}

template <std::size_t I, typename Head, typename... Tail>
inline BKSGE_CONSTEXPR Head const&
get_helper(tuple_impl<I, Head, Tail...> const& t) BKSGE_NOEXCEPT
{
	return tuple_impl<I, Head, Tail...>::head(t);
}

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_GET_HELPER_HPP
