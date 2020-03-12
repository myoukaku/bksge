/**
 *	@file	unit_test_fnd_algorithm_for_each_n.cpp
 *
 *	@brief	for_each_n のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/for_each_n.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace for_each_n_test
{

struct Sum
{
	Sum(int* p) : m_p(p) {}
	void operator()(int x) { *m_p += x; }
	Sum(Sum&& rhs) : m_p(bksge::move(rhs.m_p)) {}
	Sum& operator=(Sum&& rhs) { m_p = bksge::move(rhs.m_p); return *this; }

private:
	Sum(Sum const&) = delete;
	Sum& operator=(Sum const&) = delete;

	int* m_p;
};

GTEST_TEST(AlgorithmTest, ForEachNTest)
{
	{
		int a [] { 3, 1, 4, 1, 5 };
		auto i = bksge::for_each_n(bksge::begin(a), 5, [](int& x) { x++; });
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(2, a[3]);
		EXPECT_EQ(6, a[4]);
		EXPECT_TRUE(i == bksge::end(a));
	}
	{
		int a [] { 3, 1, 4, 1, 5 };
		auto i = bksge::for_each_n(bksge::begin(a), 3, [](int& x) { x++; });
		EXPECT_EQ(4, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(5, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(5, a[4]);
		EXPECT_TRUE(i == bksge::next(bksge::begin(a), 3));
	}
	{
		const std::array<int, 5> a {{ 3, 1, 4, 1, 5 }};
		int n = 0;
		auto i = bksge::for_each_n(bksge::begin(a), a.size(), Sum(&n));
		EXPECT_EQ(14, n);
		EXPECT_TRUE(i == bksge::end(a));
	}
	{
		const std::array<int, 5> a {{ 3, 1, 4, 1, 5 }};
		int n = 0;
		auto i = bksge::for_each_n(bksge::begin(a), a.size() - 1, Sum(&n));
		EXPECT_EQ(9, n);
		EXPECT_TRUE(i == bksge::next(bksge::begin(a), 4));
	}
	{
		std::vector<int> v { 1, 2, 3 };
		auto i = bksge::for_each_n(bksge::begin(v), v.size(), [](int& x) { x *= 2; });
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(4, v[1]);
		EXPECT_EQ(6, v[2]);
		EXPECT_TRUE(i == bksge::end(v));
	}
	{
		std::vector<int> v { 1, 2, 3 };
		auto i = bksge::for_each_n(bksge::begin(v), 1, [](int& x) { x *= 2; });
		EXPECT_EQ(2, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_TRUE(i == bksge::next(bksge::begin(v), 1));
	}
	{
		const std::list<int> l { 5, 6, 7, 8 };
		int n = 0;
		auto i = bksge::for_each_n(bksge::begin(l), l.size(), Sum(&n));
		EXPECT_EQ(26, n);
		EXPECT_TRUE(i == bksge::end(l));
	}
	{
		const std::list<int> l { 5, 6, 7, 8 };
		int n = 0;
		auto i = bksge::for_each_n(bksge::begin(l), 2, Sum(&n));
		EXPECT_EQ(11, n);
		EXPECT_TRUE(i == bksge::next(bksge::begin(l), 2));
	}
}

}	// namespace for_each_n_test

}	// namespace bksge_algorithm_test
