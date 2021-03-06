﻿/**
 *	@file	unit_test_fnd_iterator_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/empty.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, EmptyTest)
{
	{
		BKSGE_CONSTEXPR int a[3] {};
		BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::empty(a));
	}
	{
		BKSGE_CONSTEXPR float a[4] {};
		BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::empty(a));
	}
	{
		bksge::vector<int> a{};
		EXPECT_EQ(true, bksge::empty(a));
		a.push_back(10);
		EXPECT_EQ(false, bksge::empty(a));
		a.push_back(20);
		EXPECT_EQ(false, bksge::empty(a));
	}
	{
		BKSGE_CONSTEXPR bksge::array<char, 5> a {};
		BKSGE_CONSTEXPR_EXPECT_EQ(false, bksge::empty(a));
	}
	{
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(false, bksge::empty({1,2,3}));
	}
}
