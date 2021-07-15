/**
 *	@file	get_inl.hpp
 *
 *	@brief	get の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_GET_INL_HPP
#define BKSGE_FND_VARIANT_INL_GET_INL_HPP

#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/detail/exactly_once.hpp>
#include <bksge/fnd/variant/detail/index_of.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <std::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR variant_alternative_t<I, variant<Types...>>&
get(variant<Types...>& v)
{
	static_assert(I < sizeof...(Types),
		"The index must be in [0, number of alternatives)");
	if (v.index() != I)
	{
		throw_bad_variant_access(v.valueless_by_exception());
	}
	return variant_detail::variant_access::get_impl<I>(v);
}

template <std::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR variant_alternative_t<I, variant<Types...>>&&
get(variant<Types...>&& v)
{
	static_assert(I < sizeof...(Types),
		"The index must be in [0, number of alternatives)");
	if (v.index() != I)
	{
		throw_bad_variant_access(v.valueless_by_exception());
	}
	return variant_detail::variant_access::get_impl<I>(bksge::move(v));
}

template <std::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&
get(variant<Types...> const& v)
{
	static_assert(I < sizeof...(Types),
		"The index must be in [0, number of alternatives)");
	if (v.index() != I)
	{
		throw_bad_variant_access(v.valueless_by_exception());
	}
	return variant_detail::variant_access::get_impl<I>(v);
}

template <std::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&&
get(variant<Types...> const&& v)
{
	static_assert(I < sizeof...(Types),
		"The index must be in [0, number of alternatives)");
	if (v.index() != I)
	{
		throw_bad_variant_access(v.valueless_by_exception());
	}
	return variant_detail::variant_access::get_impl<I>(bksge::move(v));
}


template <typename T, typename... Types>
BKSGE_CONSTEXPR T&
get(variant<Types...>& v)
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	static_assert(!bksge::is_void<T>::value, "T must not be void");
	return bksge::get<variant_detail::index_of<T, Types...>::value>(v);
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T&&
get(variant<Types...>&& v)
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	static_assert(!bksge::is_void<T>::value, "T must not be void");
	return bksge::get<variant_detail::index_of<T, Types...>::value>(bksge::move(v));
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T const&
get(variant<Types...> const& v)
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	static_assert(!bksge::is_void<T>::value, "T must not be void");
	return bksge::get<variant_detail::index_of<T, Types...>::value>(v);
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR T const&&
get(variant<Types...> const&& v)
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	static_assert(!bksge::is_void<T>::value, "T must not be void");
	return bksge::get<variant_detail::index_of<T, Types...>::value>(bksge::move(v));
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_GET_INL_HPP
