/**
 *	@file	get_if_inl.hpp
 *
 *	@brief	get_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_GET_IF_INL_HPP
#define BKSGE_FND_VARIANT_INL_GET_IF_INL_HPP

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/detail/exactly_once.hpp>
#include <bksge/fnd/variant/detail/index_of.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <std::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR bksge::add_pointer_t<variant_alternative_t<I, variant<Types...>>>
get_if(variant<Types...>* pv) BKSGE_NOEXCEPT
{
	using alt_type = variant_alternative_t<I, variant<Types...>>;
	static_assert(I < sizeof...(Types),
		"The index must be in [0, number of alternatives)");
	static_assert(!bksge::is_void<alt_type>::value, "T must not be void");
	if (pv && pv->index() == I)
	{
		return bksge::addressof(variant_detail::variant_access::get_impl<I>(*pv));
	}
	return nullptr;
}

template <std::size_t I, typename... Types>
BKSGE_CXX14_CONSTEXPR bksge::add_pointer_t<variant_alternative_t<I, variant<Types...>> const>
get_if(variant<Types...> const* pv) BKSGE_NOEXCEPT
{
	using alt_type = variant_alternative_t<I, variant<Types...>>;
	static_assert(I < sizeof...(Types),
		"The index must be in [0, number of alternatives)");
	static_assert(!bksge::is_void<alt_type>::value, "T must not be void");
	if (pv && pv->index() == I)
	{
		return bksge::addressof(variant_detail::variant_access::get_impl<I>(*pv));
	}
	return nullptr;
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR bksge::add_pointer_t<T>
get_if(variant<Types...>* pv) BKSGE_NOEXCEPT
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	static_assert(!bksge::is_void<T>::value, "T must not be void");
	return bksge::get_if<variant_detail::index_of<T, Types...>::value>(pv);
}

template <typename T, typename... Types>
BKSGE_CONSTEXPR bksge::add_pointer_t<T const>
get_if(variant<Types...> const* pv) BKSGE_NOEXCEPT
{
	static_assert(variant_detail::exactly_once<T, Types...>::value,
		"T must occur exactly once in alternatives");
	static_assert(!bksge::is_void<T>::value, "T must not be void");
	return bksge::get_if<variant_detail::index_of<T, Types...>::value>(pv);
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_GET_IF_INL_HPP
