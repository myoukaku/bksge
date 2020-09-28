/**
 *	@file	best_match_t.hpp
 *
 *	@brief	best_match_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_BEST_MATCH_T_HPP
#define BKSGE_FND_VARIANT_DETAIL_BEST_MATCH_T_HPP

#include <bksge/fnd/variant/config.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

#if !(defined(BKSGE_MSVC) && (BKSGE_MSVC <= 1916))

struct no_narrowing_check
{
	template <typename Dest, typename Source>
	using apply = bksge::type_identity<Dest>;
};

struct narrowing_check
{
	template <typename Dest>
	static auto test_impl(Dest (&&)[1])->bksge::type_identity<Dest>;
	template <typename Dest, typename Source>
	using apply = decltype(test_impl<Dest>({bksge::declval<Source>()}));
};

template <typename Dest, typename Source>
using check_for_narrowing =
	typename bksge::conditional_t<
#if defined(BKSGE_ENABLE_NARROWING_CONVERSIONS_IN_VARIANT)
		false,
#else
		bksge::is_arithmetic<Dest>::value,
#endif
		narrowing_check,
		no_narrowing_check
	>::template apply<Dest, Source>;

template <typename T, std::size_t I>
struct overload
{
	template <typename U>
	auto operator()(T, U&&) const -> check_for_narrowing<T, U>;
};

template <typename T, std::size_t>
struct overload_bool
{
	template <typename U, typename A = bksge::remove_cvref_t<U>>
	auto operator()(bool, U&&) const
		-> bksge::enable_if_t<bksge::is_same<A, bool>::value, bksge::type_identity<T>>;
};

template <std::size_t I>
struct overload<bool, I> : overload_bool<bool, I> {};
template <std::size_t I>
struct overload<bool const, I> : overload_bool<bool const, I> {};
template <std::size_t I>
struct overload<bool volatile, I> : overload_bool<bool volatile, I> {};
template <std::size_t I>
struct overload<bool const volatile, I> : overload_bool<bool const volatile, I> {};

#if (BKSGE_CXX_STANDARD >= 17)

template <typename... Bases>
struct all_overloads : Bases...
{
	void operator()() const;
	using Bases::operator()...;
};

#else

template <typename... Bases>
struct all_overloads;

template <typename B0, typename... Bases>
struct all_overloads<B0, Bases...>
	: B0, all_overloads<Bases...>
{
	using B0::operator();
	using all_overloads<Bases...>::operator();
};

template <>
struct all_overloads<>
{
	void operator()() const;
};

#endif

template <typename IdxSeq, typename... Types>
struct make_overloads_imp;

template <std::size_t... I, typename... Types>
struct make_overloads_imp<bksge::index_sequence<I...>, Types...>
{
	using type = all_overloads<overload<Types, I>...>;
};

template <typename... Types>
using make_overloads = typename make_overloads_imp<
	bksge::make_index_sequence<sizeof...(Types)>, Types...>::type;

template <typename T, typename... Types>
using best_match_t =
	typename bksge::invoke_result_t<make_overloads<Types...>, T, T>::type;

#else

template <typename... Types>
struct overload_helper;

template <>
struct overload_helper<>
{
	void operator()() const;
};

template <typename T, typename... Types>
struct overload_helper<T, Types...>
	: public overload_helper<Types...>
{
	using overload_helper<Types...>::operator();
	bksge::type_identity<T> operator()(T) const;
};

template <typename T, typename... Types>
using best_match_t =
	typename bksge::invoke_result_t<overload_helper<Types...>, T&&>::type;

#endif

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_BEST_MATCH_T_HPP
