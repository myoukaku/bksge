/**
 *	@file	common_comparison_category.hpp
 *
 *	@brief	common_comparison_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_COMMON_COMPARISON_CATEGORY_HPP
#define BKSGE_FND_COMPARE_COMMON_COMPARISON_CATEGORY_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::common_comparison_category;
using std::common_comparison_category_t;

}	// namespace bksge

#else

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/weak_ordering.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/compare/detail/cmp_cat_id.hpp>
#include <bksge/fnd/functional/bit_or.hpp>
#include <bksge/fnd/tpp/fold_left.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename... Ts>
struct common_comparison_category
{
private:
#if defined(BKSGE_HAS_CXX17_FOLD_EXPRESSIONS)
	static constexpr unsigned cats = (detail::cmp_cat_id<Ts>::value | ...);
#else
	static constexpr unsigned cats = bksge::tpp::fold_left(bksge::bit_or<>{}, detail::cmp_cat_id<Ts>::value...);
#endif

public:
	using type =
		bksge::conditional_t<
			// If any Ti is not a comparison category type, U is void.
			bool(cats & 1),
			void,
		bksge::conditional_t<
			// Otherwise, if at least one Ti is std::partial_ordering,
			// U is std::partial_ordering.
			bool(cats & detail::cmp_cat_id<bksge::partial_ordering>::value),
			bksge::partial_ordering,
		bksge::conditional_t<
			// Otherwise, if at least one Ti is std::weak_ordering,
			// U is std::weak_ordering.
			bool(cats & detail::cmp_cat_id<bksge::weak_ordering>::value),
			bksge::weak_ordering,
			// Otherwise, U is std::strong_ordering.
			bksge::strong_ordering
		>>>;
};

// Partial specializations for one and zero argument cases.

template <typename T>
struct common_comparison_category<T>
{
	using type = void;
};

template <>
struct common_comparison_category<bksge::partial_ordering>
{
	using type = bksge::partial_ordering;
};

template <>
struct common_comparison_category<bksge::weak_ordering>
{
	using type = bksge::weak_ordering;
};

template <>
struct common_comparison_category<bksge::strong_ordering>
{
	using type = bksge::strong_ordering;
};

template <>
struct common_comparison_category<>
{
	using type = bksge::strong_ordering;
};

template <typename... Ts>
using common_comparison_category_t =
	typename common_comparison_category<Ts...>::type;


}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_COMMON_COMPARISON_CATEGORY_HPP
