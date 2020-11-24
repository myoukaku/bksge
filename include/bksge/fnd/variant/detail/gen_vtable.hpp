/**
 *	@file	gen_vtable.hpp
 *
 *	@brief	GenVtable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_GEN_VTABLE_HPP
#define BKSGE_FND_VARIANT_DETAIL_GEN_VTABLE_HPP

#include <bksge/fnd/variant/variant_size.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/detail/extra_visit_slot_needed.hpp>
#include <bksge/fnd/variant/detail/multi_array.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/variant/detail/variant_cookie.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/nth.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

// Creates a multi-dimensional vtable recursively.
//
// For example,
// visit([](auto, auto){},
//       variant<int, char>(),  // typedef'ed as V1
//       variant<float, double, long double>())  // typedef'ed as V2
// will trigger instantiations of:
// GenVtableImpl<MultiArray<void(*)(V1&&, V2&&), 2, 3>, tuple<V1&&, V2&&>, bksge::index_sequence<>>
//   GenVtableImpl<MultiArray<void(*)(V1&&, V2&&), 3>, tuple<V1&&, V2&&>, bksge::index_sequence<0>>
//     GenVtableImpl<MultiArray<void(*)(V1&&, V2&&)>, tuple<V1&&, V2&&>, bksge::index_sequence<0, 0>>
//     GenVtableImpl<MultiArray<void(*)(V1&&, V2&&)>, tuple<V1&&, V2&&>, bksge::index_sequence<0, 1>>
//     GenVtableImpl<MultiArray<void(*)(V1&&, V2&&)>, tuple<V1&&, V2&&>, bksge::index_sequence<0, 2>>
//   GenVtableImpl<MultiArray<void(*)(V1&&, V2&&), 3>, tuple<V1&&, V2&&>, bksge::index_sequence<1>>
//     GenVtableImpl<MultiArray<void(*)(V1&&, V2&&)>, tuple<V1&&, V2&&>, bksge::index_sequence<1, 0>>
//     GenVtableImpl<MultiArray<void(*)(V1&&, V2&&)>, tuple<V1&&, V2&&>, bksge::index_sequence<1, 1>>
//     GenVtableImpl<MultiArray<void(*)(V1&&, V2&&)>, tuple<V1&&, V2&&>, bksge::index_sequence<1, 2>>
// The returned multi-dimensional vtable can be fast accessed by the visitor
// using index calculation.
template <typename ArrayType, typename IndexSeq>
struct GenVtableImpl;

// Defines the apply() member that returns a MultiArray populated
// with function pointers that perform the visitation expressions e(m)
// for each valid pack of indexes into the variant types Variants.
//
// This partial specialization builds up the index sequences by recursively
// calling apply() on the next specialization of GenVtableImpl.
// The base case of the recursion defines the actual function pointers.
template <typename ResultType, typename Visitor, std::size_t... Dimensions,
	typename... Variants, std::size_t... Indices>
struct GenVtableImpl<
	variant_detail::MultiArray<ResultType (*)(Visitor, Variants...), Dimensions...>,
	bksge::index_sequence<Indices...>>
{
private:
	using Next = bksge::remove_reference_t<bksge::nth_t<sizeof...(Indices), Variants...>>;
	using ArrayType = variant_detail::MultiArray<ResultType (*)(Visitor, Variants...), Dimensions...>;

	template <std::size_t Index, typename T>
	static constexpr void
	apply_single_alt(T& element, T* cookie_element)
	{
		element         = GenVtableImpl<T, bksge::index_sequence<Indices..., Index>>::apply();
		*cookie_element = GenVtableImpl<T, bksge::index_sequence<Indices..., bksge::variant_npos>>::apply();
	}

	template <std::size_t Index, typename T>
	static constexpr void
	apply_single_alt(T& element)
	{
		auto tmp_element = GenVtableImpl<
			bksge::remove_reference_t<decltype(element)>,
			bksge::index_sequence<Indices..., Index>>::apply();
		static_assert(bksge::is_same<T, decltype(tmp_element)>::value,
			"std::visit requires the visitor to have the same "
			"return type for all alternatives of a variant");
		element = tmp_element;
	}

	template <std::size_t First, std::size_t... Rest>
	static constexpr void
	apply_all_alts(ArrayType& vtable, bksge::index_sequence<First, Rest...>, bksge::true_type)
	{
		apply_single_alt<First>(vtable.m_arr[First + 1], &(vtable.m_arr[0]));
		apply_all_alts(vtable, bksge::index_sequence<Rest...>{}, bksge::true_type{});
	}

	static constexpr void
	apply_all_alts(ArrayType&, bksge::index_sequence<>, bksge::true_type)
	{}

	template <std::size_t First, std::size_t... Rest>
	static constexpr void
	apply_all_alts(ArrayType& vtable, bksge::index_sequence<First, Rest...>, bksge::false_type)
	{
		apply_single_alt<First>(vtable.m_arr[First]);
		apply_all_alts(vtable, bksge::index_sequence<Rest...>{}, bksge::false_type{});
	}

	static constexpr void
	apply_all_alts(ArrayType&, bksge::index_sequence<>, bksge::false_type)
	{}

public:
	static constexpr ArrayType
	apply()
	{
		ArrayType vtable{};
		apply_all_alts(
			vtable,
			bksge::make_index_sequence<bksge::variant_size<Next>::value>(),
			variant_detail::extra_visit_slot_needed<ResultType, Next>{});
		return vtable;
	}
};

// This partial specialization is the base case for the recursion.
// It populates a MultiArray element with the address of a function
// that invokes the visitor with the alternatives specified by Indices.
template <typename ResultType, typename Visitor, typename... Variants, std::size_t... Indices>
struct GenVtableImpl<
	variant_detail::MultiArray<ResultType (*)(Visitor, Variants...)>,
	bksge::index_sequence<Indices...>>
{
private:
	using ArrayType = variant_detail::MultiArray<ResultType (*)(Visitor, Variants...)>;

	template <std::size_t Index, typename Variant, typename = bksge::enable_if_t<Index != bksge::variant_npos>>
	static constexpr decltype(auto)
	element_by_index_or_cookie_impl(Variant&& var, bksge::detail::overload_priority<1>) noexcept
	{
		return variant_detail::variant_access::get_impl<Index>(bksge::forward<Variant>(var));
	}

	template <std::size_t Index, typename Variant>
	static constexpr decltype(auto)
	element_by_index_or_cookie_impl(Variant&& , bksge::detail::overload_priority<0>) noexcept
	{
		return variant_detail::VariantCookie{};
	}

	template <std::size_t Index, typename Variant>
	static constexpr decltype(auto)
	element_by_index_or_cookie(Variant&& var) noexcept
	{
		return element_by_index_or_cookie_impl<Index>(
			bksge::forward<Variant>(var), bksge::detail::overload_priority<1>{});
	}

	// ResultType == VariantIdxCookie
	template <typename R = ResultType, typename = bksge::enable_if_t<bksge::is_same<R, variant_detail::VariantIdxCookie>::value>>
	static constexpr decltype(auto)
	visit_invoke_impl(Visitor&& visitor, Variants... vars, bksge::detail::overload_priority<3>)
	{
		// For raw visitation using indices, pass the indices to the visitor
		// and discard the return value:
		bksge::invoke(bksge::forward<Visitor>(visitor),
			element_by_index_or_cookie<Indices>(bksge::forward<Variants>(vars))...,
			bksge::integral_constant<std::size_t, Indices>()...);
	}

	// ResultType == VariantCookie
	template <typename R = ResultType, typename = bksge::enable_if_t<bksge::is_same<R, variant_detail::VariantCookie>::value>>
	static constexpr decltype(auto)
	visit_invoke_impl(Visitor&& visitor, Variants... vars, bksge::detail::overload_priority<2>)
	{
		// For raw visitation without indices, and discard the return value:
		bksge::invoke(bksge::forward<Visitor>(visitor),
			element_by_index_or_cookie<Indices>(bksge::forward<Variants>(vars))...);
	}

	// ArrayType::result_is_deduced
	template <typename A = ArrayType, typename = bksge::enable_if_t<A::result_is_deduced>>
	static constexpr decltype(auto)
	visit_invoke_impl(Visitor&& visitor, Variants... vars, bksge::detail::overload_priority<1>)
	{
		// For the usual std::visit case deduce the return value:
		return bksge::invoke(bksge::forward<Visitor>(visitor),
			element_by_index_or_cookie<Indices>(bksge::forward<Variants>(vars))...);
	}

	// else std::visit<R> use INVOKE<R>
	static constexpr decltype(auto)
	visit_invoke_impl(Visitor&& visitor, Variants... vars, bksge::detail::overload_priority<0>)
	{
		//return std::__invoke_r<ResultType>(
		return bksge::invoke(bksge::forward<Visitor>(visitor),
			variant_detail::variant_access::get_impl<Indices>(bksge::forward<Variants>(vars))...);
	}

	static constexpr decltype(auto)
	visit_invoke(Visitor&& visitor, Variants... vars)
	{
		return visit_invoke_impl(
			bksge::forward<Visitor>(visitor),
			bksge::forward<Variants>(vars)...,
			bksge::detail::overload_priority<3>{});
	}

	template <
		typename A = ArrayType,
		typename R = ResultType,
		typename = bksge::enable_if_t<
			A::result_is_deduced &&
			!bksge::is_same<
				typename R::type,
				decltype(visit_invoke(bksge::declval<Visitor>(), bksge::declval<Variants>()...))
			>::value
		>
	>
	static constexpr auto
	apply_impl(bksge::detail::overload_priority<1>)
	{
		struct cannot_match {};
		return cannot_match{};
	}

	static constexpr auto
	apply_impl(bksge::detail::overload_priority<0>)
	{
		return ArrayType{&visit_invoke};
	}

public:
	static constexpr auto apply()
	{
		return apply_impl(bksge::detail::overload_priority<1>{});
	}
};

template <typename ResultType, typename Visitor, typename... Variants>
struct GenVtable
{
private:
	using ArrayType = variant_detail::MultiArray<
		ResultType (*)(Visitor, Variants...),
		bksge::variant_size<bksge::remove_reference_t<Variants>>::value...>;

public:
	static constexpr ArrayType
	s_vtable = GenVtableImpl<ArrayType, bksge::index_sequence<>>::apply();
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_GEN_VTABLE_HPP
