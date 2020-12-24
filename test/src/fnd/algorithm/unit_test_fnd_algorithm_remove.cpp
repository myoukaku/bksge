/**
 *	@file	unit_test_fnd_algorithm_remove.cpp
 *
 *	@brief	remove のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/remove.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/vector.hpp>
#include <list>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace remove_test
{

struct movable_int
{
public:
	movable_int(int v) : m_value(v) {}
	movable_int(movable_int const&) = delete;
	movable_int& operator=(movable_int const&) = delete;
	movable_int(movable_int&& other) : m_value(other.m_value) { other.m_value = 0; }
	movable_int& operator=(movable_int&& other) {m_value = other.m_value; other.m_value = 0; return *this;}
	bool operator==(movable_int const& v) const { return m_value == v.m_value; }
	bool operator<(movable_int const& v) const { return m_value < v.m_value; }
private:
	int		m_value;
};

GTEST_TEST(AlgorithmTest, RemoveTest)
{
	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		EXPECT_EQ(T(2), a[0]);
		EXPECT_EQ(T(3), a[1]);
		EXPECT_EQ(T(3), a[2]);
		EXPECT_EQ(T(2), a[3]);
	}
	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 2);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
		EXPECT_EQ(T(1), a[0]);
		EXPECT_EQ(T(3), a[1]);
		EXPECT_EQ(T(1), a[2]);
		EXPECT_EQ(T(3), a[3]);
		EXPECT_EQ(T(1), a[4]);
	}
	{
		using T = movable_int;
		T a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 0);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(T(1), a[0]);
		EXPECT_EQ(T(2), a[1]);
		EXPECT_EQ(T(3), a[2]);
		EXPECT_EQ(T(1), a[3]);
		EXPECT_EQ(T(3), a[4]);
		EXPECT_EQ(T(1), a[5]);
		EXPECT_EQ(T(2), a[6]);
	}
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 1);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(2, a[3]);
	}
	{
		int a[] = {1,2,3,1,3,1,2};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 0);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(3, a[4]);
		EXPECT_EQ(1, a[5]);
		EXPECT_EQ(2, a[6]);
	}
	{
		std::array<int, 7> a = {{1,2,3,1,3,1,2}};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 3);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(1, a[3]);
		EXPECT_EQ(2, a[4]);
		EXPECT_EQ(7u, a.size());	// removeしてもコンテナのサイズは変わらない
	}
	{
		std::array<int, 4> a = {{1,1,1,1}};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 1);
		EXPECT_TRUE(ret == bksge::begin(a));
		EXPECT_EQ(4u, a.size());	// removeしてもコンテナのサイズは変わらない
	}
	{
		bksge::vector<int> a = {1,2,3,1,3,1,2,2};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 2);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 5));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(1, a[4]);
		EXPECT_EQ(8u, a.size());	// removeしてもコンテナのサイズは変わらない
	}
	{
		bksge::vector<int> a;
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 2);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(0u, a.size());
	}
	{
		std::list<int> a = {1,2,3,1,3,1,2,1,1};
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 2);
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 7));
		auto it = a.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != a.end());	// removeしてもコンテナのサイズは変わらない
	}
	{
		std::list<int> a;
		auto ret = bksge::remove(bksge::begin(a), bksge::end(a), 0);
		EXPECT_TRUE(ret == bksge::end(a));
		EXPECT_EQ(0u, a.size());
	}
}

}	// namespace remove_test

}	// namespace bksge_algorithm_test
