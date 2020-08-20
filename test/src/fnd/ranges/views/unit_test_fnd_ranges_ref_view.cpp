/**
 *	@file	unit_test_fnd_ranges_ref_view.cpp
 *
 *	@brief	ranges::ref_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/ref_view.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace ref_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int x[5] = {};
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	auto v = bksge::ranges::ref_view{ x };
#else
	auto v = bksge::ranges::ref_view<int[5]>{ x };
#endif

	static_assert(bksge::ranges::is_view<decltype(v)>::value, "");

	VERIFY(v.empty() == false);
	VERIFY(v.size() == 5);
	VERIFY(v.data() == x);
	VERIFY(v.base()[0] == 0);

	int k = 0;
	for (auto&& i : v)
	{
		i += ++k;
	}

	int const y[] = { 1, 2, 3, 4, 5 };
	VERIFY(bksge::ranges::equal(x, y));
	VERIFY(v.base()[0] == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, RefViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ref_view_test

}	// namespace bksge_ranges_test
