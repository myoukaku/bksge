/**
 *	@file	unit_test_fnd_iterator_next.cpp
 *
 *	@brief	next のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146); // 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。
BKSGE_WARNING_DISABLE_MSVC(4307); // '+': 整数定数がオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4308); // 負の整数定数が符号なしの型に変換されました。

#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <array>
#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, NextTest)
{
	{
		int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		it = bksge::next(it);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(2, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, -1);
		EXPECT_EQ(1, *it);
		it = bksge::next(it, 2);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] = {0, 1, 2, 3, 4};

		BKSGE_CONSTEXPR auto it1 = bksge::begin(a);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, *it1);
		BKSGE_CONSTEXPR auto it2 = bksge::next(it1);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, *it2);
		BKSGE_CONSTEXPR auto it3 = bksge::next(it2, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, *it3);
		BKSGE_CONSTEXPR auto it4 = bksge::next(it3, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it4);
		BKSGE_CONSTEXPR auto it5 = bksge::next(it4, 3);
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == bksge::end(a));
	}
	{
		const std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		it = bksge::next(it);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(4, *it);
		it = bksge::next(it);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(5, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		it = bksge::next(it, 3);
		EXPECT_EQ(1, *it);
		it = bksge::next(it, -1);
		EXPECT_EQ(4, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(5, *it);
		it = bksge::next(it, -4);
		EXPECT_EQ(3, *it);
		it = bksge::next(it, 5);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		it = bksge::next(it);
		EXPECT_EQ(3, *it);
		it = bksge::next(it);
		EXPECT_EQ(4, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		const std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(4, *it);
		it = bksge::next(it, -2);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, 3);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		const std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(2, *it);
		it = bksge::next(it);
		EXPECT_EQ(3, *it);
		it = bksge::next(it);
		EXPECT_EQ(4, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(3, *it);
		it = bksge::next(it, -1);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, 3);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<float, 4> a{{1, 2, 3, 4}};

		BKSGE_CXX17_CONSTEXPR auto it1 = bksge::begin(a);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it1);
		BKSGE_CXX17_CONSTEXPR auto it2 = bksge::next(it1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CXX17_CONSTEXPR auto it3 = bksge::next(it2, 2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, *it3);
		BKSGE_CXX17_CONSTEXPR auto it4 = bksge::next(it3, -1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CXX17_CONSTEXPR auto it5 = bksge::next(it4, 2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == bksge::end(a));

		BKSGE_CXX17_CONSTEXPR auto d = bksge::end(a) - bksge::begin(a);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, d);
	}
}

BKSGE_WARNING_POP();
