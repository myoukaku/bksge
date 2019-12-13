/**
 *	@file	make_derived_dimension.hpp
 *
 *	@brief	make_derived_dimension の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP
#define BKSGE_FND_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP

#include <bksge/fnd/units/detail/derived_dimension_fwd.hpp>
#include <bksge/fnd/units/detail/base_dimension_traits.hpp>
#include <bksge/fnd/tuple/tuple_sort_type.hpp>
#include <tuple>

namespace bksge
{

namespace units
{

/**
 *	@brief	derived_dimensionを作る
 *
 *	demension_holder のリストを受け取って、正規化されたderived_dimensionを返す。
 *	正規化で行う処理は
 *	・基本次元が同じものはまとめる。その際にpowerを加算する。
 *	・powerが0のものは除く
 *	・基本次元をbase_dimension_traits::orderに基いて並び替える
 */
template <typename... DimensionHolders>
struct make_derived_dimension;

namespace detail
{

// dimension_order_less
struct dimension_order_less
{
	template <typename T1, typename T2>
	using type = std::integral_constant<bool, (
		base_dimension_traits<typename T1::type>::order <
		base_dimension_traits<typename T2::type>::order
	)>;
};

// tuple_to_derived_dimension
template <typename Tuple>
struct tuple_to_derived_dimension;

template <typename... Types>
struct tuple_to_derived_dimension<std::tuple<Types...>>
{
	using type = derived_dimension<Types...>;
};

// append_dimension_impl
template <typename Head, typename Tail, typename DimensionHolder>
struct append_dimension_impl;

template <typename... Heads, typename Middle, typename... Tails, typename DimensionHolder>
struct append_dimension_impl<std::tuple<Heads...>, std::tuple<Middle, Tails...>, DimensionHolder>
{
	using type =
		typename std::conditional<
			std::is_same<typename Middle::type, typename DimensionHolder::type>::value,
			std::tuple<
				Heads...,
				dimension_holder<typename Middle::type, Middle::power + DimensionHolder::power>,
				Tails...
			>,
			typename append_dimension_impl<
				std::tuple<Heads..., Middle>,
				std::tuple<Tails...>,
				DimensionHolder
			>::type
		>::type;
};

template <typename... Heads, typename DimensionHolder>
struct append_dimension_impl<std::tuple<Heads...>, std::tuple<>, DimensionHolder>
{
	using type = std::tuple<Heads..., DimensionHolder>;
};

// append_dimension
template <typename Tuple, typename DimensionHolder>
struct append_dimension
	: public append_dimension_impl<std::tuple<>, Tuple, DimensionHolder>
{};

// remove_power0_impl
template <typename Head, typename Tail>
struct remove_power0_impl;

template <typename... Heads, typename Middle, typename... Tails>
struct remove_power0_impl<std::tuple<Heads...>, std::tuple<Middle, Tails...>>
{
	using type = typename remove_power0_impl<
		typename std::conditional<
			Middle::power != 0,
			std::tuple<Heads..., Middle>,
			std::tuple<Heads...>
		>::type,
		std::tuple<Tails...>
	>::type;
};

template <typename Head>
struct remove_power0_impl<Head, std::tuple<>>
{
	using type = Head;
};

// remove_power0
template <typename Tuple>
struct remove_power0
	: public remove_power0_impl<std::tuple<>, Tuple>
{};

// make_derived_dimension_impl
template <typename Head, typename Tail>
struct make_derived_dimension_impl;

template <typename Head, typename Middle, typename... Tails>
struct make_derived_dimension_impl<Head, std::tuple<Middle, Tails...>>
{
	using type = typename make_derived_dimension_impl<
		typename append_dimension<Head, Middle>::type,
		std::tuple<Tails...>
	>::type;
};

template <typename Head>
struct make_derived_dimension_impl<Head, std::tuple<>>
{
	using type = typename tuple_to_derived_dimension<
		typename bksge::tuple_sort_type<
			typename remove_power0<Head>::type,
			dimension_order_less
		>::type
	>::type;
};

}	// namespace detail

template <typename... DimensionHolders>
struct make_derived_dimension
	: public detail::make_derived_dimension_impl<std::tuple<>, std::tuple<DimensionHolders...>>
{};

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP
