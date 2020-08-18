/**
 *	@file	unit_test_fnd_iterator_distance.cpp
 *
 *	@brief	distance のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/config.hpp>
#include <vector>
#include <list>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_iterator_test
{

namespace distance_test
{

GTEST_TEST(IteratorTest, DistanceTest)
{
	{
		int a[] = {0,1,2};
		EXPECT_EQ(3, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		const int a[] = {0,1,2};
		EXPECT_EQ(3, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_CONSTEXPR int a[] = {0,1,2};
		BKSGE_CXX14_CONSTEXPR auto d = bksge::distance(bksge::begin(a), bksge::end(a));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, d);
	}
	{
		std::vector<float> v {3,1,4,1,5};
		EXPECT_EQ(5, bksge::distance(bksge::begin(v), bksge::end(v)));
	}
	{
		const std::vector<float> v {3,1,4,1,5};
		EXPECT_EQ(5, bksge::distance(bksge::begin(v), bksge::end(v)));
	}
	{
		std::list<int> l {2, 3, 4, 5};
		EXPECT_EQ(4, bksge::distance(bksge::begin(l), bksge::end(l)));
	}
	{
		const std::list<int> l {2, 3, 4, 5};
		EXPECT_EQ(4, bksge::distance(bksge::begin(l), bksge::end(l)));
	}
	{
		std::array<float, 2> a{{1, 2}};
		EXPECT_EQ(2, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		const std::array<float, 3> a{{1, 2, 3}};
		EXPECT_EQ(3, bksge::distance(bksge::begin(a), bksge::end(a)));
	}
	{
		BKSGE_CONSTEXPR std::array<float, 4> a{{1, 2, 3, 4}};
		BKSGE_CXX17_CONSTEXPR auto d = bksge::distance(bksge::begin(a), bksge::end(a));
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, d);
	}
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[10] ={};
	VERIFY(bksge::ranges::distance(a) == 10);

	test_random_access_range<int> c(a);
	VERIFY(bksge::ranges::distance(c) == 10);

	auto b = c.begin();
	auto e = c.end();
	auto ei = bksge::ranges::next(b, e);
	VERIFY(bksge::ranges::distance(b, e) == 10);
	VERIFY(bksge::ranges::distance(ei, b) == -10);

	const auto cb = b;
	const auto ce = e;
	const auto cei = ei;
	VERIFY(bksge::ranges::distance(cb, ce) == 10);
	VERIFY(bksge::ranges::distance(cei, cb) == -10);

	test_random_access_sized_range<int> c2(a);
	VERIFY(bksge::ranges::distance(c2) == 10);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[2] ={};
	VERIFY(bksge::ranges::distance(a) == 2);

	test_bidirectional_range<int> c(a);
	VERIFY(bksge::ranges::distance(c) == 2);

	auto b = c.begin();
	auto e = c.end();
	VERIFY(bksge::ranges::distance(b, e) == 2);

	const auto cb = b;
	const auto ce = e;
	VERIFY(bksge::ranges::distance(cb, ce) == 2);

	test_bidirectional_sized_range<int> c2(a);
	VERIFY(bksge::ranges::distance(c2) == 2);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	int a[3] ={};
	test_forward_range<int> c(a);
	VERIFY(bksge::ranges::distance(c) == 3);

	auto b = c.begin();
	auto e = c.end();
	VERIFY(bksge::ranges::distance(b, e) == 3);

	const auto cb = b;
	const auto ce = e;
	VERIFY(bksge::ranges::distance(cb, ce) == 3);

	test_forward_sized_range<int> c2(a);
	VERIFY(bksge::ranges::distance(c2) == 3);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	int a[4] ={};
	test_input_range<int> c(a);
	static_assert(bksge::ranges::is_range<decltype(c)>::value, "");

	VERIFY(bksge::ranges::distance(c) == 4);

	c = test_input_range<int>(a);
	auto b = c.begin();
	auto e = c.end();
	VERIFY(bksge::ranges::distance(b, e) == 4);

	test_input_range<int> c2(a);
	const auto cb = c2.begin();
	const auto ce = c2.end();
	VERIFY(bksge::ranges::distance(cb, ce) == 4);

	test_input_sized_range<int> c3(a);
	VERIFY(bksge::ranges::distance(c3) == 4);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	int a[5] ={};
	test_output_range<int> c(a);
	VERIFY(bksge::ranges::distance(c) == 5);

	test_output_range<int> c2(a);
	auto b = c2.begin();
	auto e = c2.end();
	VERIFY(bksge::ranges::distance(b, e) == 5);

	test_output_range<int> c3(a);
	const auto cb = c3.begin();
	const auto ce = c3.end();
	VERIFY(bksge::ranges::distance(cb, ce) == 5);

	test_output_sized_range<int> c4(a);
	VERIFY(bksge::ranges::distance(c4) == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, RangesDistanceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace distance_test

}	// namespace bksge_iterator_test
