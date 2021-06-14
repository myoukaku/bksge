/**
 *	@file	tuple_sort_type_inl.hpp
 *
 *	@brief	tuple_sort_type の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_INL_TUPLE_SORT_TYPE_INL_HPP
#define BKSGE_FND_TUPLE_INL_TUPLE_SORT_TYPE_INL_HPP

#include <bksge/fnd/tuple/tuple_sort_type.hpp>
#include <bksge/fnd/tuple/tuple_init_type.hpp>
#include <bksge/fnd/tuple/tuple_last_type.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>

namespace bksge
{

namespace detail
{

// tuple_sort_type_impl_2
template <typename Head, typename Tail, typename Compare>
struct tuple_sort_type_impl_2;

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename T1,
	typename T2,
	typename... Tails,
	typename Compare
>
struct tuple_sort_type_impl_2<
	Tuple<Heads...>, Tuple<T1, T2, Tails...>, Compare
>
{
	using type =
		bksge::conditional_t<
			//(T1::value < T2::value),
			(Compare::template type<T1, T2>::value),
			typename tuple_sort_type_impl_2<
				Tuple<Heads..., T1>,
				Tuple<T2, Tails...>,
				Compare
			>::type,
			typename tuple_sort_type_impl_2<
				Tuple<Heads..., T2>,
				Tuple<T1, Tails...>,
				Compare
			>::type
		>;
};

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename T,
	typename Compare
>
struct tuple_sort_type_impl_2<
	Tuple<Heads...>, Tuple<T>, Compare
>
{
	using type = Tuple<Heads..., T>;
};

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename Compare
>
struct tuple_sort_type_impl_2<
	Tuple<Heads...>, Tuple<>, Compare
>
{
	using type = Tuple<Heads...>;
};

// tuple_sort_type_impl
template <typename Head, typename Tail, typename Compare>
struct tuple_sort_type_impl
{
	using type = Tail;
};

template <
	template <typename...> class Tuple,
	typename H1,
	typename... Heads,
	typename... Tails,
	typename Compare
>
struct tuple_sort_type_impl<
	Tuple<H1, Heads...>, Tuple<Tails...>, Compare
>
{
	using tmp =
		typename tuple_sort_type_impl_2<
			Tuple<>,
			Tuple<H1, Heads...>,
			Compare
		>::type;

	using type = typename tuple_sort_type_impl<
		bksge::tuple_init_type_t<tmp>,
		Tuple<bksge::tuple_last_type_t<tmp>, Tails...>,
		Compare
	>::type;
};

}	// namespace detail

// tuple_sort_type
template <
	template <typename...> class Tuple,
	typename... Types,
	typename Compare
>
struct tuple_sort_type<Tuple<Types...>, Compare>
	: public detail::tuple_sort_type_impl<
		Tuple<Types...>, Tuple<>, Compare
	>
{};

template <typename Tuple, typename Compare>
struct tuple_sort_type<Tuple const, Compare>
	: public tuple_sort_type<Tuple, Compare> {};

template <typename Tuple, typename Compare>
struct tuple_sort_type<Tuple volatile, Compare>
	: public tuple_sort_type<Tuple, Compare> {};

template <typename Tuple, typename Compare>
struct tuple_sort_type<Tuple const volatile, Compare>
	: public tuple_sort_type<Tuple, Compare> {};

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_INL_TUPLE_SORT_TYPE_INL_HPP
