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
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

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
	using type = bksge::bool_constant<(
		base_dimension_traits<typename T1::type>::order <
		base_dimension_traits<typename T2::type>::order
	)>;
};

// tuple_to_derived_dimension
template <typename Tuple>
struct tuple_to_derived_dimension;

template <typename... Types>
struct tuple_to_derived_dimension<bksge::tuple<Types...>>
{
	using type = derived_dimension<Types...>;
};

// append_dimension_impl
template <typename Head, typename Tail, typename DimensionHolder>
struct append_dimension_impl;

template <typename... Heads, typename Middle, typename... Tails, typename DimensionHolder>
struct append_dimension_impl<bksge::tuple<Heads...>, bksge::tuple<Middle, Tails...>, DimensionHolder>
{
	using type =
		bksge::conditional_t<
			bksge::is_same<typename Middle::type, typename DimensionHolder::type>::value,
			bksge::tuple<
				Heads...,
				dimension_holder<typename Middle::type, Middle::power + DimensionHolder::power>,
				Tails...
			>,
			typename append_dimension_impl<
				bksge::tuple<Heads..., Middle>,
				bksge::tuple<Tails...>,
				DimensionHolder
			>::type
		>;
};

template <typename... Heads, typename DimensionHolder>
struct append_dimension_impl<bksge::tuple<Heads...>, bksge::tuple<>, DimensionHolder>
{
	using type = bksge::tuple<Heads..., DimensionHolder>;
};

// append_dimension
template <typename Tuple, typename DimensionHolder>
struct append_dimension
	: public append_dimension_impl<bksge::tuple<>, Tuple, DimensionHolder>
{};

// remove_power0_impl
template <typename Head, typename Tail>
struct remove_power0_impl;

template <typename... Heads, typename Middle, typename... Tails>
struct remove_power0_impl<bksge::tuple<Heads...>, bksge::tuple<Middle, Tails...>>
{
	using type = typename remove_power0_impl<
		bksge::conditional_t<
			Middle::power != 0,
			bksge::tuple<Heads..., Middle>,
			bksge::tuple<Heads...>
		>,
		bksge::tuple<Tails...>
	>::type;
};

template <typename Head>
struct remove_power0_impl<Head, bksge::tuple<>>
{
	using type = Head;
};

// remove_power0
template <typename Tuple>
struct remove_power0
	: public remove_power0_impl<bksge::tuple<>, Tuple>
{};

// make_derived_dimension_impl
template <typename Head, typename Tail>
struct make_derived_dimension_impl;

template <typename Head, typename Middle, typename... Tails>
struct make_derived_dimension_impl<Head, bksge::tuple<Middle, Tails...>>
{
	using type = typename make_derived_dimension_impl<
		typename append_dimension<Head, Middle>::type,
		bksge::tuple<Tails...>
	>::type;
};

template <typename Head>
struct make_derived_dimension_impl<Head, bksge::tuple<>>
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
	: public detail::make_derived_dimension_impl<bksge::tuple<>, bksge::tuple<DimensionHolders...>>
{};

}	// namespace units

}	// namespace bksge

#endif // BKSGE_FND_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP
