/**
 *	@file	unit_test_fnd_algorithm_for_each.cpp
 *
 *	@brief	for_each のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/for_each.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace for_each_test
{

struct Sum
{
	Sum() : n(0) {}
	void operator()(int x) { n += x; }
	int get() const { return n; }
	Sum(Sum&& rhs) : n(bksge::move(rhs.n)) {}
	Sum& operator=(Sum&& rhs) { n = bksge::move(rhs.n); return *this; }

private:
	Sum(Sum const&) = delete;
	Sum& operator=(Sum const&) = delete;

	int n;
};

GTEST_TEST(AlgorithmTest, ForEachTest)
{
	{
		int a [] { 3, 1, 4, 1, 5 };
		auto f = bksge::for_each(bksge::begin(a), bksge::end(a), [](int& x) { x++; });
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(6, a[4]);

		int n = 2;
		f(n);
		EXPECT_EQ(3, n);
	}
	{
		const std::array<int, 5> a {{ 3, 1, 4, 1, 5 }};
		auto s = bksge::for_each(bksge::begin(a), bksge::end(a), Sum());
		EXPECT_EQ(14, s.get());
	}
	{
		bksge::vector<int> v { 1, 2, 3 };
		auto f = bksge::for_each(bksge::begin(v), bksge::end(v), [](int& x) { x *= 2; });
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(6, v[2]);

		int n = 2;
		f(n);
		EXPECT_EQ(4, n);
	}
	{
		const bksge::list<int> l { 5, 6, 7, 8 };
		auto s = bksge::for_each(bksge::begin(l), bksge::end(l), Sum());
		EXPECT_EQ(26, s.get());
	}
}

}	// namespace for_each_test

}	// namespace bksge_algorithm_test
