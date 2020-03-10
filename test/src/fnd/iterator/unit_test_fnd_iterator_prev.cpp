/**
 *	@file	unit_test_fnd_iterator_prev.cpp
 *
 *	@brief	prev のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146); // 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。
BKSGE_WARNING_DISABLE_MSVC(4308); // 負の整数定数が符号なしの型に変換されました。

#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <array>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(IteratorTest, PrevTest)
{
	{
		int a[] = {0,1,2};

		auto it = bksge::end(a);
		it = bksge::prev(it);
		EXPECT_EQ(2, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		const int a[] = {0,1,2};

		auto it = bksge::end(a);
		it = bksge::prev(it, 2);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(2, *it);
		it = bksge::prev(it, 2);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] = {0, 1, 2, 3, 4};

		BKSGE_CONSTEXPR auto it1 = bksge::end(a);
		BKSGE_CONSTEXPR auto it2 = bksge::prev(it1);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, *it2);
		BKSGE_CONSTEXPR auto it3 = bksge::prev(it2, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it3);
		BKSGE_CONSTEXPR auto it4 = bksge::prev(it3, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CONSTEXPR auto it5 = bksge::prev(it4, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, *it5);
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == bksge::begin(a));
	}
	{
		const bksge::vector<float> v {3,1,4,1,5};

		auto it = bksge::end(v);
		it = bksge::prev(it);
		EXPECT_EQ(5, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it == bksge::begin(v));
	}
	{
		bksge::vector<float> v {3,1,4,1,5};

		auto it = bksge::end(v);
		it = bksge::prev(it, 3);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it, 2);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it, -3);
		EXPECT_EQ(5, *it);
		it = bksge::prev(it, 4);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it == bksge::begin(v));
	}
	{
		bksge::list<int> l {2, 3, 4};

		auto it = bksge::end(l);
		it = bksge::prev(it);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it);
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it == bksge::begin(l));
	}
	{
		const bksge::list<int> l {2, 3, 4};

		auto it = bksge::end(l);
		it = bksge::prev(it, 2);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it, 2);
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it == bksge::begin(l));
	}
	{
		const std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::end(a);
		it = bksge::prev(it);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it);
		EXPECT_EQ(2, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::end(a);
		it = bksge::prev(it, 2);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it, 3);
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int,5> a {{0, 1, 2, 3, 4}};

		BKSGE_CXX17_CONSTEXPR auto it1 = bksge::end(a);
		BKSGE_CXX17_CONSTEXPR auto it2 = bksge::prev(it1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, *it2);
		BKSGE_CXX17_CONSTEXPR auto it3 = bksge::prev(it2, 2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it3);
		BKSGE_CXX17_CONSTEXPR auto it4 = bksge::prev(it3, -1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CXX17_CONSTEXPR auto it5 = bksge::prev(it4, 3);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(0, *it5);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == bksge::begin(a));
	}
}

BKSGE_WARNING_POP();
