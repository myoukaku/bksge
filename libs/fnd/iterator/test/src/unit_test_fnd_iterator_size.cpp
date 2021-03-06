﻿/**
 *	@file	unit_test_fnd_iterator_size.cpp
 *
 *	@brief	size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/size.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, SizeTest)
{
	{
		BKSGE_CONSTEXPR int a[3] {};
		BKSGE_CONSTEXPR_EXPECT_EQ(3u, bksge::size(a));
	}
	{
		BKSGE_CONSTEXPR float a[4] {};
		BKSGE_CONSTEXPR_EXPECT_EQ(4u, bksge::size(a));
	}
	{
		bksge::vector<int> a{};
		EXPECT_EQ(0u, bksge::size(a));
		a.push_back(10);
		EXPECT_EQ(1u, bksge::size(a));
		a.push_back(20);
		EXPECT_EQ(2u, bksge::size(a));
	}
	{
		BKSGE_CONSTEXPR bksge::array<char, 5> a {};
		BKSGE_CONSTEXPR_EXPECT_EQ(5u, bksge::size(a));
	}
	{
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3u, bksge::size({1,2,3}));
	}
}
