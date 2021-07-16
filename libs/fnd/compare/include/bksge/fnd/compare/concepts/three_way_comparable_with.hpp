/**
 *	@file	three_way_comparable_with.hpp
 *
 *	@brief	three_way_comparable_with の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP
#define BKSGE_FND_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(BKSGE_USE_STD_COMPARE) && defined(BKSGE_HAS_CXX20_CONCEPTS)

#include <compare>

namespace bksge
{

using std::three_way_comparable_with;

}	// namespace bksge

#else	// defined(BKSGE_USE_STD_COMPARE)

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable.hpp>
#include <bksge/fnd/compare/detail/compares_as.hpp>
#include <bksge/fnd/concepts/common_reference_with.hpp>
#include <bksge/fnd/concepts/detail/weakly_eq_cmp_with.hpp>
#include <bksge/fnd/concepts/detail/partially_ordered_with.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/common_reference.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U, typename Cat = bksge::partial_ordering>
concept three_way_comparable_with =
	bksge::three_way_comparable<T, Cat> &&
	bksge::three_way_comparable<U, Cat> &&
	bksge::common_reference_with<
		bksge::remove_reference_t<T> const&,
		bksge::remove_reference_t<U> const&> &&
	bksge::three_way_comparable<
		bksge::common_reference_t<
			bksge::remove_reference_t<T> const&,
			bksge::remove_reference_t<U> const&
		>, Cat> &&
	detail::weakly_eq_cmp_with<T, U> &&
	detail::partially_ordered_with<T, U> &&
	requires(
		bksge::remove_reference_t<T> const& t,
		bksge::remove_reference_t<U> const& u)
	{
		{ t <=> u } -> detail::compares_as<Cat>;
		{ u <=> t } -> detail::compares_as<Cat>;
	};

#else	// defined(BKSGE_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, typename U, typename Cat>
struct three_way_comparable_with_impl
{
private:
	template <typename T2, typename U2, typename C2,
		typename = bksge::enable_if_t<bksge::three_way_comparable<T2, C2>>,
		typename = bksge::enable_if_t<bksge::three_way_comparable<U2, C2>>,
		typename = bksge::enable_if_t<bksge::common_reference_with<
			bksge::remove_reference_t<T2> const&,
			bksge::remove_reference_t<U2> const&> &&
		typename = bksge::enable_if_t<bksge::three_way_comparable<
			bksge::common_reference_t<
				bksge::remove_reference_t<T2> const&,
				bksge::remove_reference_t<U2> const&
			>, C2>>,
		typename = bksge::enable_if_t<detail::weakly_eq_cmp_with<T2, U2>>,
		typename = bksge::enable_if_t<detail::partially_ordered_with<T2, U2>>,
		typename A = bksge::remove_reference_t<T2>,
		typename B = bksge::remove_reference_t<U2>,
		typename R1 = decltype(std::declval<A const&>() <=> std::declval<B const&>()),
		typename R2 = decltype(std::declval<B const&>() <=> std::declval<A const&>())
	>
	static auto test(int) -> bksge::conjunction<
		detail::compares_as<R1, C2>,
		detail::compares_as<R2, C2>
	>;

	template <typename T2, typename U2, typename C2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U, Cat>(0));
};

}	// namespace detail

template <typename T, typename U, typename Cat = bksge::partial_ordering>
using three_way_comparable_with =
	typename detail::three_way_comparable_with_impl<T, U, Cat>::type;

#endif	// defined(BKSGE_HAS_CXX20_CONCEPTS)

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_COMPARE)

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // BKSGE_FND_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_WITH_HPP
