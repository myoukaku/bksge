/**
 *	@file	unit_test_fnd_algorithm_search.cpp
 *
 *	@brief	search のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/search.hpp>
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

namespace search_test
{

GTEST_TEST(AlgorithmTest, SearchTest)
{
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1,2,3,4 };

		const auto it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 0));
	}
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 1,2,4 };

		const auto it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const std::array<int, 3> b = {{ 1,2,3 }};

		const auto it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 0));
	}
	{
		const int a[] = { 1,2,3,4,1,2,3,1,2,1 };
		const std::array<int, 3> b = {{ 1,2,3 }};
		const auto it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::begin(b));
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		const std::vector<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 2,3 };

		auto const it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int x, int y){return x == y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 1));
	}
	{
		const bksge::list<int> a = { 1,2,3,4,1,2,3,1,2,1 };
		const int b[] = { 3,4 };

		auto const it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 2));
	}
	{
		const std::array<int, 10> a = {{ 1,2,3,4,1,2,3,1,2,1 }};
		const bksge::list<int> b = { 3,1,2 };

		auto const it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), [](int x, int y){return x == y; });
		EXPECT_TRUE(it == bksge::next(bksge::begin(a), 6));
	}
	{
		const bksge::list<int> a {1,2,3};
		const std::vector<int> b;

		auto const it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		const bksge::list<int> a;
		const std::vector<int> b {1,2,3};

		auto const it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const bksge::list<int> a;
		const std::vector<int> b;

		auto const it = bksge::search(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(it == bksge::begin(a));
	}
}

}	// namespace search_test

}	// namespace bksge_algorithm_test
