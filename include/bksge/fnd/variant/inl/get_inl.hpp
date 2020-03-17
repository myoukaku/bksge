/**
 *	@file	get_inl.hpp
 *
 *	@brief	get の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_GET_INL_HPP
#define BKSGE_FND_VARIANT_INL_GET_INL_HPP

#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/detail/find_exactly_one_t.hpp>
#include <bksge/fnd/variant/holds_alternative.hpp>
#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace variant_detail
{

template <std::size_t I, typename V>
inline BKSGE_CONSTEXPR auto generic_get(V&& v)
->decltype((variant_detail::access::variant_t::get_alt<I>(bksge::forward<V>(v)).m_value))
{
#if !(defined(_MSC_VER) && (_MSC_VER <= 1916))
	return
		(!holds_alternative_impl<I>(v) ? throw_bad_variant_access() : (void)0),
		variant_detail::access::variant_t::get_alt<I>(bksge::forward<V>(v)).m_value;
#else
	// Visual Studio 2017 のバグを回避
	if (!holds_alternative_impl<I>(v))
	{
		throw_bad_variant_access();
	}

	return variant_detail::access::variant_t::get_alt<I>(bksge::forward<V>(v)).m_value;
#endif
}

}	// namespace variant_detail

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>>&
get(variant<Types...>& v)
{
	static_assert(I < sizeof...(Types), "");
	static_assert(!bksge::is_void<variant_alternative_t<I, variant<Types...>>>::value, "");
	return variant_detail::generic_get<I>(v);
}

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>>&&
get(variant<Types...>&& v)
{
	static_assert(I < sizeof...(Types), "");
	static_assert(!bksge::is_void<variant_alternative_t<I, variant<Types...>>>::value, "");
	return variant_detail::generic_get<I>(bksge::move(v));
}

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&
get(variant<Types...> const& v)
{
	static_assert(I < sizeof...(Types), "");
	static_assert(!bksge::is_void<variant_alternative_t<I, variant<Types...>>>::value, "");
	return variant_detail::generic_get<I>(v);
}

template <std::size_t I, typename... Types>
inline BKSGE_CONSTEXPR variant_alternative_t<I, variant<Types...>> const&&
get(variant<Types...> const&& v)
{
	static_assert(I < sizeof...(Types), "");
	static_assert(!bksge::is_void<variant_alternative_t<I, variant<Types...>>>::value, "");
	return variant_detail::generic_get<I>(bksge::move(v));
}

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR T& get(variant<Types...>& v)
{
	static_assert(!bksge::is_void<T>::value, "");
	return bksge::get<variant_detail::find_exactly_one_t<T, Types...>::value>(v);
}

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR T&& get(variant<Types...>&& v)
{
	static_assert(!bksge::is_void<T>::value, "");
	return bksge::get<variant_detail::find_exactly_one_t<T, Types...>::value>(bksge::move(v));
}

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR T const& get(variant<Types...> const& v)
{
	static_assert(!bksge::is_void<T>::value, "");
	return bksge::get<variant_detail::find_exactly_one_t<T, Types...>::value>(v);
}

template <typename T, typename... Types>
inline BKSGE_CONSTEXPR T const&& get(variant<Types...> const&& v)
{
	static_assert(!bksge::is_void<T>::value, "");
	return bksge::get<variant_detail::find_exactly_one_t<T, Types...>::value>(bksge::move(v));
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_GET_INL_HPP
