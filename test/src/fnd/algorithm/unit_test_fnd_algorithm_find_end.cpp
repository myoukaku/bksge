/**
 *	@file	unit_test_fnd_algorithm_find_end.cpp
 *
 *	@brief	find_end のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/find_end.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <gtest/gtest.h>
#include <array>
#include <forward_list>
#include <list>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace find_end_test
{

GTEST_TEST(AlgorithmTest, FindEndTest)
{
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1,2,3,4 };
		const auto it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 0));
	}
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1,2,4 };
		const auto it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const std::array<int, 3> b = {{ 1,2,3 }};
		const auto it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const std::array<int, 3> b = {{ 1,2,3 }};
		const auto it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::begin(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::vector<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int x, int y){return x == y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 9));
	}
	{
		const std::list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1,2,3 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const std::array<int, 10> a = {{ 1,2,3,4,1,2,3,1,2,1 }};
		const std::list<int> b = { 1,2,3 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int x, int y){return x == y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const std::list<int> a {1,2,3};
		const std::vector<int> b;
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::list<int> a;
		const std::vector<int> b {1,2,3};
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::list<int> a;
		const std::vector<int> b;
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::forward_list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1,2,3 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const std::forward_list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const std::array<int, 3> b = {{ 1,2,3 }};
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const std::forward_list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const std::vector<int> b = { 1,2,3 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const std::forward_list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const std::list<int> b = { 1,2,3 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
	{
		const std::forward_list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const std::forward_list<int> b = { 1,2,3 };
		auto const it = bksge::find_end(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 4));
	}
}

}	// namespace find_end_test

}	// namespace bksge_algorithm_test
