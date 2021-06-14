/**
 *	@file	three_way_comparable.hpp
 *
 *	@brief	three_way_comparable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_HPP
#define BKSGE_FND_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#if defined(BKSGE_USE_STD_COMPARE) && defined(BKSGE_HAS_CXX20_CONCEPTS)

#include <compare>

namespace bksge
{

using std::three_way_comparable;

}	// namespace bksge

#else	// defined(BKSGE_USE_STD_COMPARE)

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/detail/compares_as.hpp>
#include <bksge/fnd/concepts/detail/weakly_eq_cmp_with.hpp>
#include <bksge/fnd/concepts/detail/partially_ordered_with.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename Cat = bksge::partial_ordering>
concept three_way_comparable =
	detail::weakly_eq_cmp_with<T, T> &&
	detail::partially_ordered_with<T, T> &&
	requires(
		bksge::remove_reference_t<T> const& a,
		bksge::remove_reference_t<T> const& b)
	{
		{ a <=> b } -> detail::compares_as<Cat>;
	};

#else	// defined(BKSGE_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, typename Cat>
struct three_way_comparable_impl
{
private:
	template <typename T2, typename C2,
		typename = bksge::enable_if_t<bksge::conjunction<
			detail::weakly_eq_cmp_with<T2, T2>,
			detail::partially_ordered_with<T2, T2>
		>::value>,
		typename A = bksge::remove_reference_t<T2>,
		typename R = decltype(
			bksge::declval<A const&>() <=> bksge::declval<A const&>())
	>
	static auto test(int) -> detail::compares_as<R, C2>;

	template <typename T2, typename C2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, Cat>(0));
};

}	// namespace detail

template <typename T, typename Cat = bksge::partial_ordering>
using three_way_comparable =
	typename detail::three_way_comparable_impl<T, Cat>::type;

#endif	// defined(BKSGE_HAS_CXX20_CONCEPTS)

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_COMPARE)

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

#endif // BKSGE_FND_COMPARE_CONCEPTS_THREE_WAY_COMPARABLE_HPP
