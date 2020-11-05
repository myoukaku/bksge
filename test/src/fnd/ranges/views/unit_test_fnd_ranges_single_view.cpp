/**
 *	@file	unit_test_fnd_ranges_single_view.cpp
 *
 *	@brief	ranges::single_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/single_view.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_ranges_test
{

namespace single_view_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int n = 4;
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	bksge::ranges::single_view s{n};
#else
	bksge::ranges::single_view<int> s{n};
#endif
	static_assert(bksge::is_same<bksge::ranges::range_value_t<decltype(s)>, int>::value, "");
	VERIFY(bksge::ranges::size(s) == 1);

	int count = 0;
	for (auto i : s)
	{
		VERIFY(i == 4);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*bksge::ranges::begin(s) == 4);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	bksge::ranges::single_view<long> const s2 {};
	static_assert(bksge::is_same<bksge::ranges::range_value_t<decltype(s2)>, long>::value, "");
	VERIFY(bksge::ranges::size(s2) == 1);

	int count = 0;
	for (auto l : s2)
	{
		VERIFY(l == 0L);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*bksge::ranges::begin(s2) == 0L);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	bksge::ranges::single_view<float> s2(bksge::in_place, 0.5f);
	static_assert(bksge::is_same<bksge::ranges::range_value_t<decltype(s2)>, float>::value, "");
	VERIFY(bksge::ranges::size(s2) == 1);

	int count = 0;
	for (auto l : s2)
	{
		VERIFY(l == 0.5f);
		++count;
	}

	VERIFY(count == 1);
	VERIFY(*bksge::ranges::begin(s2) == 0.5f);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	auto s3 = bksge::ranges::views::single('a');
	static_assert(bksge::is_same<bksge::ranges::range_value_t<decltype(s3)>, char>::value, "");
	VERIFY(bksge::ranges::size(s3) == 1);
	VERIFY(*bksge::ranges::begin(s3) == 'a');

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SingleViewTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace single_view_test

}	// namespace bksge_ranges_test
