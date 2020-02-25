/**
 *	@file	unit_test_fnd_algorithm_transform.cpp
 *
 *	@brief	transform のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/transform.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <gtest/gtest.h>
#include <array>
#include <iterator>
#include <list>
#include <vector>

namespace bksge_algorithm_test
{

namespace transform_test
{

struct Doubling
{
	template <typename T>
	T operator()(T x) const
	{
		return x * 2;
	}
};

int to_int(float f)
{
	return static_cast<int>(f);
}

GTEST_TEST(AlgorithmTest, TransformTest)
{
// Unary Operator

	// int[3] => int[3]
	{
		const int a1[] {0,1,2};
		int a2[3];
		auto const it = bksge::transform(
			bksge::begin(a1), bksge::end(a1), bksge::begin(a2), Doubling());

		EXPECT_EQ(0, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(4, a2[2]);

		EXPECT_TRUE(it == bksge::end(a2));
	}
	// int[3] => int[3] (self assign)
	{
		int a1[] {0,1,2};
		auto const it = bksge::transform(
			bksge::begin(a1), bksge::end(a1), bksge::begin(a1), Doubling());

		EXPECT_EQ(0, a1[0]);
		EXPECT_EQ(2, a1[1]);
		EXPECT_EQ(4, a1[2]);

		EXPECT_TRUE(it == bksge::end(a1));
	}
	// array => array
	{
		const std::array<int, 3> a1 {{0,1,2}};
		std::array<int, 3> a2;
		auto const it = bksge::transform(
			bksge::begin(a1), bksge::end(a1), bksge::begin(a2), Doubling());

		EXPECT_EQ(0, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(4, a2[2]);

		EXPECT_TRUE(it == bksge::end(a2));
	}
	// vector => array
	{
		const std::vector<int> v1 { 1, 2, 3 };
		std::array<int, 3> a1;
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1), bksge::begin(a1), Doubling());

		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(4, a1[1]);
		EXPECT_EQ(6, a1[2]);

		EXPECT_TRUE(it == bksge::end(a1));
	}
	// vector => int[4]
	{
		const std::vector<int> v1 { 1, 2, 3 };
		int a1[4]{};
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1), bksge::begin(a1), Doubling());

		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(4, a1[1]);
		EXPECT_EQ(6, a1[2]);
		EXPECT_EQ(0, a1[3]);

		EXPECT_TRUE(it == bksge::begin(a1) + 3);
	}
	// vector => vector
	{
		const std::vector<int> v1 { 1, 2, 3 };
		std::vector<int> v2 { 10, 11, 12, 13, 14 };
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1), bksge::begin(v2), Doubling());

		EXPECT_EQ( 2, v2[0]);
		EXPECT_EQ( 4, v2[1]);
		EXPECT_EQ( 6, v2[2]);
		EXPECT_EQ(13, v2[3]);
		EXPECT_EQ(14, v2[4]);

		EXPECT_TRUE(it == bksge::begin(v2) + 3);
	}
	// vector => vector (back_inserter)
	{
		const std::vector<int> v1 { 1, 2, 3 };
		std::vector<int> v2;
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1), std::back_inserter(v2), Doubling());

		EXPECT_EQ( 3u, v2.size());
		EXPECT_EQ( 2, v2[0]);
		EXPECT_EQ( 4, v2[1]);
		EXPECT_EQ( 6, v2[2]);

		(void)it;
	}
	// vector => list (back_inserter)
	{
		const std::vector<int> v1 { 1, 2, 3 };
		std::list<int> l1;
		bksge::transform(
			bksge::begin(v1), bksge::end(v1), std::back_inserter(l1), Doubling());

		auto it = l1.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_TRUE(it == l1.end());
	}
	// float[] => vector<int> (back_inserter)
	{
		const float a1[] {1.5, 2.5};
		std::vector<int> v1;
		auto const it = bksge::transform(
			bksge::begin(a1), bksge::end(a1), std::back_inserter(v1), to_int);

		EXPECT_EQ(2u, v1.size());
		EXPECT_EQ(1, v1[0]);
		EXPECT_EQ(2, v1[1]);

		(void)it;
	}
	// float[] => list<int> (back_inserter)
	{
		const float a1[] {1.5, 2.5, 3.5};
		std::list<int> l1;
		bksge::transform(
			bksge::begin(a1), bksge::end(a1), std::back_inserter(l1), to_int);

		auto it = l1.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == l1.end());
	}

// Binary Operator

	// vector, vector => vector
	{
		const std::vector<int> v1 { 1, 2, 3 };
		const std::vector<int> v2 { 4, 5, 6 };
		std::vector<int> v3 (3);
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(v2), bksge::end(v2),
			bksge::begin(v3),
			bksge::plus<>());

		EXPECT_EQ(5, v3[0]);
		EXPECT_EQ(7, v3[1]);
		EXPECT_EQ(9, v3[2]);
		EXPECT_TRUE(it == bksge::end(v3));
	}

	// vector, vector => vector (self assign)
	{
		std::vector<int> v1 { 1, 2, 3 };
		const std::vector<int> v2 { 4, 5, 6 };
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(v2), bksge::end(v2),
			bksge::begin(v1),
			bksge::plus<>());

		EXPECT_EQ(5, v1[0]);
		EXPECT_EQ(7, v1[1]);
		EXPECT_EQ(9, v1[2]);
		EXPECT_TRUE(it == bksge::end(v1));
	}

	// vector, vector => array
	{
		const std::vector<int> v1 { 1, 2, 3, 4 };
		const std::vector<int> v2 { 4, 5, 6 };
		std::array<int, 4> a1{{}};
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(v2), bksge::end(v2),
			bksge::begin(a1),
			bksge::plus<>());

		EXPECT_EQ(5, a1[0]);
		EXPECT_EQ(7, a1[1]);
		EXPECT_EQ(9, a1[2]);
		EXPECT_EQ(0, a1[3]);
		EXPECT_TRUE(it == bksge::begin(a1) + 3);
	}

	// vector, vector => int[]
	{
		const std::vector<int> v1 { 1, 2, 3 };
		const std::vector<int> v2 { 4, 5, 6, 7 };
		int a1[5] {};
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(v2), bksge::end(v2),
			bksge::begin(a1),
			bksge::plus<>());

		EXPECT_EQ(5, a1[0]);
		EXPECT_EQ(7, a1[1]);
		EXPECT_EQ(9, a1[2]);
		EXPECT_EQ(0, a1[3]);
		EXPECT_EQ(0, a1[4]);
		EXPECT_TRUE(it == bksge::begin(a1) + 3);
	}

	// vector, vector => list
	{
		const std::vector<int> v1 { 1, 2, 3, 4 };
		const std::vector<int> v2 { 4, 5, 6, 7 };
		std::list<int> l1;
		bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(v2), bksge::end(v2),
			std::back_inserter(l1),
			bksge::plus<>());

		auto it = l1.begin();
		EXPECT_EQ( 5, *it++);
		EXPECT_EQ( 7, *it++);
		EXPECT_EQ( 9, *it++);
		EXPECT_EQ(11, *it++);
		EXPECT_TRUE(it == l1.end());
	}

	// vector, array  => int[]
	{
		const std::vector<int> v1 { 1, 2, 3, 4 };
		const std::array<int, 3> a1 {{ 4, 5, 6 }};
		int a2[3];
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(a1), bksge::end(a1),
			bksge::begin(a2),
			bksge::plus<>());

		EXPECT_EQ(5, a2[0]);
		EXPECT_EQ(7, a2[1]);
		EXPECT_EQ(9, a2[2]);
		EXPECT_TRUE(it == bksge::end(a2));
	}
	// list,   vector => array
	{
		const std::list<int>   l1 { 10, 11, 12 };
		const std::vector<int> v1 { 13, 14, 15, 16 };
		std::array<int, 3> a1;
		auto const it = bksge::transform(
			bksge::begin(l1), bksge::end(l1),
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(a1),
			bksge::plus<>());

		EXPECT_EQ(23, a1[0]);
		EXPECT_EQ(25, a1[1]);
		EXPECT_EQ(27, a1[2]);
		EXPECT_TRUE(it == bksge::end(a1));
	}

	// int[],  vector => list
	{
		const int a1[] = { 17, 18, 19 };
		const std::vector<int> v1 { 20, 21, 22 };
		std::list<int> l1;
		bksge::transform(
			bksge::begin(a1), bksge::end(a1),
			bksge::begin(v1), bksge::end(v1),
			std::back_inserter(l1),
			bksge::plus<>());

		auto it = l1.begin();
		EXPECT_EQ(37, *it++);
		EXPECT_EQ(39, *it++);
		EXPECT_EQ(41, *it++);
		EXPECT_TRUE(it == l1.end());
	}

	// int[],  vector => int[] (self assign)
	{
		int a1[] = { 17, 18, 19, 20 };
		const std::vector<int> v1 { 20, 21, 22 };
		auto const it = bksge::transform(
			bksge::begin(a1), bksge::end(a1),
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(a1),
			bksge::plus<>());

		EXPECT_EQ(37, a1[0]);
		EXPECT_EQ(39, a1[1]);
		EXPECT_EQ(41, a1[2]);
		EXPECT_EQ(20, a1[3]);
		EXPECT_TRUE(it == bksge::begin(a1) + 3);
	}

	// vector, array  => array (self assign)
	{
		const std::vector<int> v1 { 20, 21, 22 };
		std::array<int, 3> a1 {{23, 24, 25}};
		auto const it = bksge::transform(
			bksge::begin(v1), bksge::end(v1),
			bksge::begin(a1), bksge::end(a1),
			bksge::begin(a1),
			bksge::plus<>());

		EXPECT_EQ(43, a1[0]);
		EXPECT_EQ(45, a1[1]);
		EXPECT_EQ(47, a1[2]);
		EXPECT_TRUE(it == bksge::end(a1));
	}
}

}	// namespace transform_test

}	// namespace bksge_algorithm_test
