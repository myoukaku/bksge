/**
 *	@file	unit_test_fnd_algorithm_copy.cpp
 *
 *	@brief	copy のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/copy.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/back_inserter.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_algorithm_test
{

namespace copy_test
{

GTEST_TEST(AlgorithmTest, CopyTest)
{
	{
		const int a[] { 1, 2, 3 };
		bksge::array<int, 3> b {{}};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[3];

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[5] {};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const int a[] { 1, 2, 3 };
		bksge::array<int, 3> b {{}};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[3];

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[2];

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[5] {};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const int a[] { 1, 2, 3 };
		bksge::array<int, 5> b {{}};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 3));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(0, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const int a[] { 1, 2, 3 };
		bksge::array<int, 2> b {{}};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
	}
	{
		const bksge::array<int, 4> a {{ 4, 5, 6, 7 }};
		bksge::vector<int> b(5);

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 4));

		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(6, b[2]);
		EXPECT_EQ(7, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::array<int, 4> a {{ 4, 5, 6, 7 }};
		bksge::vector<int> b(5);

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 4));

		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(6, b[2]);
		EXPECT_EQ(7, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::array<int, 4> a {{ 4, 5, 6, 7 }};
		bksge::vector<int> b(3);

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(6, b[2]);
	}
	{
		const bksge::vector<int> a { 5, 6, 7, 8, 9 };
		bksge::list<int> b;

		bksge::copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));

		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a { 5, 6, 7, 8, 9 };
		bksge::list<int> b { 1, 2, 3 };

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::vector<int> a { 5, 6, 7, 8, 9 };
		bksge::list<int> b { 1, 2, 3, 4, 5, 6, 7 };

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 5));

		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const bksge::list<int> a { 1, 2, 3, 4 };
		int b[5] {};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 4));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(4, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const bksge::list<int> a { 1, 2, 3, 4 };
		int b[3] {};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b));
		EXPECT_TRUE(ret == bksge::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		const bksge::vector<int> a;
		bksge::list<int> b;

		bksge::copy(bksge::begin(a), bksge::end(a), bksge::back_inserter(b));

		EXPECT_TRUE(b.empty());
	}
	{
		const bksge::list<int> a;
		int b[3] {};

		auto ret = bksge::copy(bksge::begin(a), bksge::end(a), bksge::begin(b));
		EXPECT_TRUE(ret == bksge::next(bksge::begin(b), 0));

		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
	}
}

}	// namespace copy_test

}	// namespace bksge_algorithm_test
