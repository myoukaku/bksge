/**
 *	@file	unit_test_fnd_compare_common_comparison_category.cpp
 *
 *	@brief	common_comparison_category のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/common_comparison_category.hpp>
#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/weak_ordering.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>

namespace bksge_compare_test
{

namespace common_comparison_category_test
{

using bksge::common_comparison_category_t;
using bksge::partial_ordering;
using bksge::weak_ordering;
using bksge::strong_ordering;

static_assert(bksge::is_same<strong_ordering,  common_comparison_category_t<>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<int>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<int, int>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<partial_ordering, int>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<weak_ordering, int>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<strong_ordering, int>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<int, partial_ordering>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<int, weak_ordering>>(), "");
static_assert(bksge::is_same<void,             common_comparison_category_t<int, strong_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<partial_ordering>>(), "");
static_assert(bksge::is_same<weak_ordering,    common_comparison_category_t<weak_ordering>>(), "");
static_assert(bksge::is_same<strong_ordering,  common_comparison_category_t<strong_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<partial_ordering, partial_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<partial_ordering, weak_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<partial_ordering, strong_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<weak_ordering, partial_ordering>>(), "");
static_assert(bksge::is_same<weak_ordering,    common_comparison_category_t<weak_ordering, weak_ordering>>(), "");
static_assert(bksge::is_same<weak_ordering,    common_comparison_category_t<weak_ordering, strong_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<strong_ordering, partial_ordering>>(), "");
static_assert(bksge::is_same<weak_ordering,    common_comparison_category_t<strong_ordering, weak_ordering>>(), "");
static_assert(bksge::is_same<strong_ordering,  common_comparison_category_t<strong_ordering, strong_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<strong_ordering, partial_ordering, strong_ordering, strong_ordering>>(), "");
static_assert(bksge::is_same<partial_ordering, common_comparison_category_t<strong_ordering, partial_ordering, strong_ordering, weak_ordering>>(), "");
static_assert(bksge::is_same<weak_ordering,    common_comparison_category_t<strong_ordering, weak_ordering,    strong_ordering, weak_ordering>>(), "");
static_assert(bksge::is_same<strong_ordering,  common_comparison_category_t<strong_ordering, strong_ordering,  strong_ordering, strong_ordering>>(), "");

}	// namespace common_comparison_category_test

}	// namespace bksge_compare_test
