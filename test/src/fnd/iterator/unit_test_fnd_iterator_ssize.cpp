/**
 *	@file	unit_test_fnd_iterator_ssize.cpp
 *
 *	@brief	ssize のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/ssize.hpp>
#include <bksge/fnd/type_traits/is_signed.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, SSizeTest)
{
	{
		BKSGE_CONSTEXPR int a[3] {};
		static_assert(bksge::is_signed<decltype(bksge::ssize(a))>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::ssize(a));
	}
	{
		BKSGE_CONSTEXPR float a[4] {};
		static_assert(bksge::is_signed<decltype(bksge::ssize(a))>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::ssize(a));
	}
	{
		bksge::vector<int> a{};
		static_assert(bksge::is_signed<decltype(bksge::ssize(a))>::value, "");
		EXPECT_EQ(0, bksge::ssize(a));
		a.push_back(10);
		EXPECT_EQ(1, bksge::ssize(a));
		a.push_back(20);
		EXPECT_EQ(2, bksge::ssize(a));
	}
	{
		BKSGE_CONSTEXPR std::array<char, 5> a {};
		static_assert(bksge::is_signed<decltype(bksge::ssize(a))>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, bksge::ssize(a));
	}
	{
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, bksge::ssize({1,2,3}));
		static_assert(bksge::is_signed<decltype(bksge::ssize({1,2,3}))>::value, "");
	}
}
