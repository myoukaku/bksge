/**
 *	@file	unit_test_fnd_algorithm_rotate.cpp
 *
 *	@brief	rotate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/rotate.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <array>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace rotate_test
{

class Foo
{
public:
	Foo(int value) : m_value(value) {}
	Foo(Foo&& other) : m_value(bksge::move(other.m_value)) {}
	Foo& operator=(Foo&& other) { m_value = bksge::move(other.m_value); return *this; }
	int get() const { return m_value; }
private:
	int	m_value;
};

GTEST_TEST(AlgorithmTest, RotateTest)
{
	{
		int a[] { 1,2,3 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
	}
	{
		int a[] { 1,2,3 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		EXPECT_EQ(2, a[0]);
		EXPECT_EQ(3, a[1]);
		EXPECT_EQ(1, a[2]);
	}
	{
		int a[] { 1,2,3 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
	}
	{
		int a[] { 1,2,3 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 3), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
	}
	{
		int a[] { 42 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		EXPECT_EQ(42, a[0]);
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		EXPECT_EQ(1, a[0].get());
		EXPECT_EQ(2, a[1].get());
		EXPECT_EQ(3, a[2].get());
		EXPECT_EQ(4, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		EXPECT_EQ(2, a[0].get());
		EXPECT_EQ(3, a[1].get());
		EXPECT_EQ(4, a[2].get());
		EXPECT_EQ(1, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		EXPECT_EQ(3, a[0].get());
		EXPECT_EQ(4, a[1].get());
		EXPECT_EQ(1, a[2].get());
		EXPECT_EQ(2, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 3), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		EXPECT_EQ(4, a[0].get());
		EXPECT_EQ(1, a[1].get());
		EXPECT_EQ(2, a[2].get());
		EXPECT_EQ(3, a[3].get());
	}
	{
		Foo a[] { Foo(1), Foo(2), Foo(3), Foo(4) };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 4), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_EQ(1, a[0].get());
		EXPECT_EQ(2, a[1].get());
		EXPECT_EQ(3, a[2].get());
		EXPECT_EQ(4, a[3].get());
	}
	{
		std::array<int, 4> a {{ 1,2,3,4 }};
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		EXPECT_EQ(3, a[0]);
		EXPECT_EQ(4, a[1]);
		EXPECT_EQ(1, a[2]);
		EXPECT_EQ(2, a[3]);
	}
	{
		std::array<int, 4> a {{ 1,2,3,4 }};
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 4), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_EQ(1, a[0]);
		EXPECT_EQ(2, a[1]);
		EXPECT_EQ(3, a[2]);
		EXPECT_EQ(4, a[3]);
	}
	{
		bksge::vector<int> a { 1,2,3,4,5 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 4), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		EXPECT_EQ(5, a[0]);
		EXPECT_EQ(1, a[1]);
		EXPECT_EQ(2, a[2]);
		EXPECT_EQ(3, a[3]);
		EXPECT_EQ(4, a[4]);
	}
	{
		bksge::vector<int> a;
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
	{
		bksge::list<int> a { 1, 2 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::list<int> a { 1, 2, 3, 4 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 3), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		auto it = a.begin();
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::list<int> a { 1, 2, 3, 4 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 2));
		auto it = a.begin();
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::list<int> a;
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 0), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 0));
		EXPECT_TRUE(a.empty());
	}
	{
		bksge::forward_list<int> a { 1,2,3,4,5 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 1), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 4));
		auto it = a.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::forward_list<int> a { 1,2,3,4,5 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 2), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 3));
		auto it = a.begin();
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it == a.end());
	}
	{
		bksge::forward_list<int> a { 1,2,3,4,5 };
		auto ret = bksge::rotate(bksge::begin(a), bksge::next(bksge::begin(a), 4), bksge::end(a));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(a), 1));
		auto it = a.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == a.end());
	}
}

}	// namespace rotate_test

}	// namespace bksge_algorithm_test
