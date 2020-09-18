/**
 *	@file	unit_test_fnd_ranges_common_view.cpp
 *
 *	@brief	ranges::common_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/common_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/cbegin.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/algorithm/count.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace common_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 1, 3};
	auto v = x | views::common;
	using V = decltype(v);
	static_assert(ranges::is_common_range<V>::value, "");
	static_assert(ranges::is_view<V>::value, "");
	static_assert(ranges::is_random_access_range<V>::value, "");
	static_assert(bksge::is_same_as<V, decltype(views::common(v))>::value, "");

	VERIFY(bksge::count(v.begin(), v.end(), 1) == 2);

	auto v2 = v | (views::common | views::common);
	VERIFY(bksge::count(v2.begin(), v2.end(), 1) == 2);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 1, 3};
	test_random_access_sized_range<int> rx(x);
	auto v = rx | views::common;
	using V = decltype(v);
	static_assert(ranges::is_common_range<V>::value, "");
	static_assert(ranges::is_view<V>::value, "");
	static_assert(ranges::is_forward_range<V>::value, "");
	static_assert(bksge::is_same_as<V, decltype(views::common(v))>::value, "");

	VERIFY(v.size() == 4);
	VERIFY(ranges::size(v) == 4);

	VERIFY(bksge::count(v.begin(), v.end(), 1) == 2);

	{
		auto i1 = ranges::begin(v);
		auto i2 = ranges::cbegin(v);
		VERIFY(i1 != ranges::end(v));
		VERIFY(i2 != ranges::cend(v));
	}

	VERIFY(v.base().begin() == rx.begin());
	VERIFY(views::common(v).base().begin() == rx.begin());

	auto const v2 = v | (views::common | views::common);
	VERIFY(v2.size() == 4);
	VERIFY(bksge::count(v2.begin(), v2.end(), 1) == 2);

	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;
	namespace views  = ranges::views;

	int x[] = {1, 2, 1, 3};
	test_forward_range<int> rx(x);
	auto v = rx | views::common;
	using V = decltype(v);
	static_assert(ranges::is_common_range<V>::value, "");
	static_assert(ranges::is_view<V>::value, "");
	static_assert(ranges::is_forward_range<V>::value, "");
	static_assert(bksge::is_same_as<V, decltype(views::common(v))>::value, "");

	VERIFY(bksge::count(v.begin(), v.end(), 1) == 2);

	{
		auto i1 = ranges::begin(v);
		auto i2 = ranges::cbegin(v);
		VERIFY(i1 != ranges::end(v));
		VERIFY(i2 != ranges::cend(v));
	}

	auto v2 = v | (views::common | views::common);
	VERIFY(bksge::count(v2.begin(), v2.end(), 1) == 2);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CommonViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace common_view_test

}	// namespace bksge_ranges_test
