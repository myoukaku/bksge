/**
 *	@file	unit_test_fnd_numeric_inner_product.cpp
 *
 *	@brief	inner_product のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/inner_product.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(NumericTest, InnerProductTest)
{
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		EXPECT_EQ(32, x1);
		auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 10);
		EXPECT_EQ(42, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST int a1[] = {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9 };
		BKSGE_CONSTEXPR_OR_CONST int a2[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
		BKSGE_CXX14_CONSTEXPR auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(735, x1);
		BKSGE_CXX14_CONSTEXPR auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 10);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(745, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST int a1[] = { 2 };
		BKSGE_CONSTEXPR_OR_CONST int a2[] = { 3 };
		BKSGE_CXX14_CONSTEXPR auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(6, x1);
		BKSGE_CXX14_CONSTEXPR auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 10);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(16, x2);
	}
	{
		std::array<int, 3> a1 = {{ 2, 3, 4 }};
		std::array<int, 3> a2 = {{ 4, 5, 6 }};
		auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		EXPECT_EQ(47, x1);
		auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 20);
		EXPECT_EQ(67, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a2 = {{ 4, 5, 6 }};
		BKSGE_CXX17_CONSTEXPR auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(47, x1);
		BKSGE_CXX17_CONSTEXPR auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 20);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(67, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 4 }};
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a2 = {{ 6 }};
		BKSGE_CXX17_CONSTEXPR auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(24, x1);
		BKSGE_CXX17_CONSTEXPR auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 20);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(44, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		BKSGE_CONSTEXPR_OR_CONST int a2[] = { 4, 5, 6 };
		BKSGE_CXX17_CONSTEXPR auto x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(47, x1);
		BKSGE_CXX17_CONSTEXPR auto x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 20);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(67, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		const bksge::vector<int> v1 = {{ 4, 5, 6 }};
		auto const x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(v1), 0);
		EXPECT_EQ(47, x1);
		auto const x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(v1), 20);
		EXPECT_EQ(67, x2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 3> a1 = {{ 2, 3, 4 }};
		const bksge::list<int> l1 = {{ 4, 5, 6 }};
		auto const x1 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(l1), 0);
		EXPECT_EQ(47, x1);
		auto const x2 = bksge::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(l1), 20);
		EXPECT_EQ(67, x2);
	}
	{
		bksge::vector<int> v1 = { 3, 4, 5, 6 };
		bksge::vector<int> v2 = { 5, 6, 7, 8 };
		auto x1 = bksge::inner_product(bksge::begin(v1), bksge::end(v1), bksge::begin(v2), 0);
		EXPECT_EQ(122, x1);
		auto x2 = bksge::inner_product(bksge::begin(v1), bksge::end(v1), bksge::begin(v2), 30);
		EXPECT_EQ(152, x2);
	}
	{
		bksge::vector<int> v1 = { 3, 4, 5, 6 };
		bksge::list<int> l1 = { 5, 6, 7, 8 };
		auto x1 = bksge::inner_product(bksge::begin(v1), bksge::end(v1), bksge::begin(l1), 0);
		EXPECT_EQ(122, x1);
		auto x2 = bksge::inner_product(bksge::begin(v1), bksge::end(v1), bksge::begin(l1), 30);
		EXPECT_EQ(152, x2);
	}
	{
		bksge::vector<int> v1;
		bksge::vector<int> v2;
		auto x1 = bksge::inner_product(bksge::begin(v1), bksge::end(v1), bksge::begin(v2), 0);
		EXPECT_EQ(0, x1);
		auto x2 = bksge::inner_product(bksge::begin(v1), bksge::end(v1), bksge::begin(v2), 30);
		EXPECT_EQ(30, x2);
	}
	{
		bksge::list<int> l1 = { 1, 2, 3, 4, 5 };
		bksge::list<int> l2 = { 6, 7, 8, 9, 10 };
		auto x1 = bksge::inner_product(bksge::begin(l1), bksge::end(l1), bksge::begin(l2), 0);
		EXPECT_EQ(130, x1);
		auto x2 = bksge::inner_product(bksge::begin(l1), bksge::end(l1), bksge::begin(l2), 40);
		EXPECT_EQ(170, x2);
	}
	{
		bksge::list<int> l1;
		bksge::list<int> l2;
		auto x1 = bksge::inner_product(bksge::begin(l1), bksge::end(l1), bksge::begin(l2), 0);
		EXPECT_EQ(0, x1);
		auto x2 = bksge::inner_product(bksge::begin(l1), bksge::end(l1), bksge::begin(l2), 40);
		EXPECT_EQ(40, x2);
	}
}
