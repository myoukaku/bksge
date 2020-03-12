/**
 *	@file	unit_test_fnd_algorithm_search_n.cpp
 *
 *	@brief	search_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/search_n.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace search_n_test
{

GTEST_TEST(AlgorithmTest, SearchNTest)
{
	{
		const int a[] = { 1,2,3,2,1,3,3,2,3,3,1 };
		const auto it = bksge::search_n(bksge::begin(a), bksge::end(a), 0, 3);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		const std::array<int, 11> a = {{ 1,2,3,2,1,3,3,2,3,3,1 }};
		const auto it = bksge::search_n(bksge::begin(a), bksge::end(a), 1, 3);
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 2));
	}
	{
		const int a[] = { 1,2,3,2,1,3,3,2,3,3,1 };
		const auto it = bksge::search_n(bksge::begin(a), bksge::end(a), 2, 3);
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 5));
	}
	{
		const std::array<int, 11> a = {{ 1,2,3,2,1,3,3,2,3,3,1 }};
		const auto it = bksge::search_n(bksge::begin(a), bksge::end(a), 3, 3);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const std::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 1, 2);
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 1));
	}
	{
		const bksge::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 2, 2);
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 3));
	}
	{
		const std::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 3, 2);
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 6));
	}
	{
		const bksge::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 3, 2, [](int x, int y) { return x <= y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 3));
	}
	{
		const std::vector<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 3, 2, [](int x, int y) { return x >= y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 1));
	}
	{
		const bksge::list<int> a = { 1,2,3,2,2,1,2,2,2,3,4 };
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 0, 5);
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 0));
	}
	{
		const std::vector<int> a;
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 2, 3);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::list<int> a;
		auto const it = bksge::search_n(bksge::begin(a), bksge::end(a), 2, 3);
		EXPECT_TRUE(it == bksge::begin(a));
	}
}

}	// namespace search_n_test

}	// namespace bksge_algorithm_test
