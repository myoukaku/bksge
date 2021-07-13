/**
 *	@file	visit.hpp
 *
 *	@brief	visit の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VISIT_HPP
#define BKSGE_FND_VARIANT_VISIT_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_USE_STD_VARIANT)

namespace bksge
{

using std::visit;

}	// namespace bksge

#else

#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/variant/variant_size.hpp>
#include <bksge/fnd/variant/detail/deduce_visit_result.hpp>
#include <bksge/fnd/variant/detail/do_visit.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/tpp/any_of.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename T, typename... Types>
struct same_types : public bksge::conjunction<bksge::is_same<T, Types>...> {};

template <typename Visitor, typename Variant, bksge::size_t... Idxs>
constexpr bool check_visitor_results(bksge::index_sequence<Idxs...>)
{
	return same_types<bksge::invoke_result_t<
		Visitor, decltype(bksge::get<Idxs>(bksge::declval<Variant>()))>...>::value;
}

template <typename Visitor, typename... Variants>
struct VisitResult
{
	using type = bksge::invoke_result_t<Visitor,
		decltype(bksge::get<0>(bksge::declval<Variants>()))...>;
};

template <typename Visitor, typename... Variants>
using VisitResultT = typename VisitResult<Visitor, Variants...>::type;

// sizeof...(Variants) != 1
template <typename Visitor, typename... Variants>
constexpr VisitResultT<Visitor, Variants...>
visit_impl(bksge::false_type, Visitor&& visitor, Variants&&... variants)
{
	using ResultType = bksge::invoke_result_t<Visitor,
		decltype(bksge::get<0>(bksge::declval<Variants>()))...>;

	using Tag = variant_detail::DeduceVisitResult<ResultType>;

	return variant_detail::do_visit<Tag>(
		bksge::forward<Visitor>(visitor),
		bksge::forward<Variants>(variants)...);
}

// sizeof...(Variants) == 1
template <typename Visitor, typename... Variants>
constexpr VisitResultT<Visitor, Variants...>
visit_impl(bksge::true_type, Visitor&& visitor, Variants&&... variants)
{
	constexpr bool visit_rettypes_match =
		variant_detail::check_visitor_results<Visitor, Variants...>(
			bksge::make_index_sequence<
			bksge::variant_size<bksge::remove_reference_t<Variants>...>::value>());
	static_assert(visit_rettypes_match,
		"bksge::visit requires the visitor to have the same "
		"return type for all alternatives of a variant");

	return variant_detail::visit_impl(
		bksge::false_type{},
		bksge::forward<Visitor>(visitor),
		bksge::forward<Variants>(variants)...);
}

}	// namespace variant_detail

template <typename Visitor, typename... Variants>
constexpr variant_detail::VisitResultT<Visitor, Variants...>
visit(Visitor&& visitor, Variants&&... variants)
{
	if (bksge::tpp::any_of(variants.valueless_by_exception()...))
	{
		throw_bad_variant_access("bksge::visit: variant is valueless");
	}

	return variant_detail::visit_impl(
		bksge::bool_constant<sizeof...(Variants) == 1>{},
		bksge::forward<Visitor>(visitor),
		bksge::forward<Variants>(variants)...);
}

template <typename Res, typename Visitor, typename... Variants>
constexpr Res
visit(Visitor&& visitor, Variants&&... variants)
{
	if (bksge::tpp::any_of(variants.valueless_by_exception()...))
	{
		throw_bad_variant_access("bksge::visit<R>: variant is valueless");
	}

	return variant_detail::do_visit<Res>(
		bksge::forward<Visitor>(visitor),
		bksge::forward<Variants>(variants)...);
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_VARIANT_VISIT_HPP
