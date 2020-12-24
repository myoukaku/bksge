/**
 *	@file	unit_test_fnd_iterator_data.cpp
 *
 *	@brief	data のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/data.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, DataTest)
{
	{
		BKSGE_CONSTEXPR int a[3] {};
		BKSGE_CONSTEXPR_EXPECT_EQ(&a[0], bksge::data(a));
	}
	{
		BKSGE_CONSTEXPR float a[4] {};
		BKSGE_CONSTEXPR_EXPECT_EQ(&a[0], bksge::data(a));
	}
	{
		bksge::vector<int> a{};
		EXPECT_EQ(nullptr, bksge::data(a));
		a.push_back(10);
		EXPECT_EQ(&a[0], bksge::data(a));
		a.push_back(20);
		EXPECT_EQ(&a[0], bksge::data(a));
	}
	{
		BKSGE_CONSTEXPR std::array<char, 5> a {};
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(&a[0], bksge::data(a));
	}
	{
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, *bksge::data({1,2,3}));
	}
}
