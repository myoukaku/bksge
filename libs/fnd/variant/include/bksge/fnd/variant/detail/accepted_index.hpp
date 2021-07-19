/**
 *	@file	accepted_index.hpp
 *
 *	@brief	accepted_index の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_ACCEPTED_INDEX_HPP
#define BKSGE_FND_VARIANT_DETAIL_ACCEPTED_INDEX_HPP

#include <bksge/fnd/variant/variant_size.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace variant_detail
{

// Helper used to check for valid conversions that don't involve narrowing.
template <typename T>
struct Arr { T m_x[1]; };

// "Build an imaginary function FUN(Ti) for each alternative type Ti"
template <std::size_t Index, typename T, typename Ti, typename = void>
struct Build_FUN
{
	// This function means 'using Build_FUN<I, T, Ti>::fun;' is valid,
	// but only static functions will be considered in the call below.
	void fun();
};

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wdeprecated-volatile");

// "... for which Ti x[] = {std::forward<T>(t)}; is well-formed."
template <std::size_t Index, typename T, typename Ti>
struct Build_FUN<Index, T, Ti, bksge::void_t<decltype(Arr<Ti>{ { std::declval<T>() }})>>
{
	// This is the FUN function for type Ti, with index Index
	static bksge::integral_constant<std::size_t, Index> fun(Ti);
};

BKSGE_WARNING_POP();

template <typename T, typename Variant,
	typename = bksge::make_index_sequence<bksge::variant_size<Variant>::value>>
struct Build_FUNs;

#if 0
template <typename T, typename... Ti, std::size_t... Indices>
struct Build_FUNs<T, variant<Ti...>, bksge::index_sequence<Indices...>>
	: public Build_FUN<Indices, T, Ti>...
{
	using Build_FUN<Indices, T, Ti>::fun...;
};
#else
template <typename T, typename T0, typename... Ti, std::size_t I0, std::size_t... Indices>
struct Build_FUNs<T, variant<T0, Ti...>, bksge::index_sequence<I0, Indices...>>
	: public Build_FUN<I0, T, T0>
	, public Build_FUNs<T, variant<Ti...>, bksge::index_sequence<Indices...>>
{
	using Build_FUN<I0, T, T0>::fun;
	using Build_FUNs<T, variant<Ti...>, bksge::index_sequence<Indices...>>::fun;
};

template <typename T, typename T0, std::size_t I0>
struct Build_FUNs<T, variant<T0>, bksge::index_sequence<I0>>
	: public Build_FUN<I0, T, T0>
{
	using Build_FUN<I0, T, T0>::fun;
};
#endif

// The index j of the overload FUN(Tj) selected by overload resolution
// for FUN(std::forward<T>(t))
template <typename T, typename Variant>
using FUN_type = decltype(Build_FUNs<T, Variant>::fun(std::declval<T>()));

// The index selected for FUN(std::forward<T>(t)), or variant_npos if none.
template <typename T, typename Variant, typename = void>
struct accepted_index
	: public bksge::integral_constant<std::size_t, bksge::variant_npos>
{};

template <typename T, typename Variant>
struct accepted_index<T, Variant, bksge::void_t<FUN_type<T, Variant>>>
	: public FUN_type<T, Variant>
{};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_ACCEPTED_INDEX_HPP
