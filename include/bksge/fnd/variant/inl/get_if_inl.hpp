/**
 *	@file	get_if_inl.hpp
 *
 *	@brief	get_if の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_GET_IF_INL_HPP
#define BKSGE_FND_VARIANT_INL_GET_IF_INL_HPP

#include <bksge/fnd/variant/get_if.hpp>
#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/holds_alternative.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <std::size_t I, typename V>
inline BKSGE_CONSTEXPR auto generic_get_if(V* v) BKSGE_NOEXCEPT
->decltype(bksge::addressof(variant_detail::access::variant_t::get_alt<I>(*v).m_value))
{
	return v && holds_alternative_impl<I>(*v) ?
		bksge::addressof(variant_detail::access::variant_t::get_alt<I>(*v).m_value) :
		nullptr;
}

}	// namespace variant_detail

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR bksge::add_pointer_t<variant_alternative_t<I, variant<Types...>>>
get_if(variant<Types...>* v) BKSGE_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "");
	static_assert(!bksge::is_void<variant_alternative_t<I, variant<Types...>>>::value, "");
	return variant_detail::generic_get_if<I>(v);
}

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR bksge::add_pointer_t<variant_alternative_t<I, variant<Types...>> const>
get_if(variant<Types...> const* v) BKSGE_NOEXCEPT
{
	static_assert(I < sizeof...(Types), "");
	static_assert(!bksge::is_void<variant_alternative_t<I, variant<Types...>>>::value, "");
	return variant_detail::generic_get_if<I>(v);
}

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR bksge::add_pointer_t<T>
get_if(variant<Types...>* v) BKSGE_NOEXCEPT
{
	static_assert(!bksge::is_void<T>::value, "");
	return bksge::get_if<variant_detail::find_exactly_one_t<T, Types...>::value>(v);
}

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR bksge::add_pointer_t<T const>
get_if(variant<Types...> const* v) BKSGE_NOEXCEPT
{
	static_assert(!bksge::is_void<T>::value, "");
	return bksge::get_if<variant_detail::find_exactly_one_t<T, Types...>::value>(v);
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_GET_IF_INL_HPP
