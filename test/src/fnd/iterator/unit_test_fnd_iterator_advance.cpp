/**
 *	@file	unit_test_fnd_iterator_advance.cpp
 *
 *	@brief	advance のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/advance.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_iterator_test
{

namespace advance_test
{

GTEST_TEST(IteratorTest, AdvanceTest)
{
	{
		int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		bksge::advance(it);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(2, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(2, *it);
		bksge::advance(it, -1);
		EXPECT_EQ(1, *it);
		bksge::advance(it, 2);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		bksge::advance(it);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(4, *it);
		bksge::advance(it);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(5, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		bksge::advance(it, 3);
		EXPECT_EQ(1, *it);
		bksge::advance(it, -1);
		EXPECT_EQ(4, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(5, *it);
		bksge::advance(it, -4);
		EXPECT_EQ(3, *it);
		bksge::advance(it, 5);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		bksge::advance(it);
		EXPECT_EQ(3, *it);
		bksge::advance(it);
		EXPECT_EQ(4, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(4, *it);
		bksge::advance(it, -2);
		EXPECT_EQ(2, *it);
		bksge::advance(it, 3);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		bksge::advance(it);
		EXPECT_EQ(2, *it);
		bksge::advance(it);
		EXPECT_EQ(3, *it);
		bksge::advance(it);
		EXPECT_EQ(4, *it);
		bksge::advance(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		bksge::advance(it, 2);
		EXPECT_EQ(3, *it);
		bksge::advance(it, -1);
		EXPECT_EQ(2, *it);
		bksge::advance(it, 3);
		EXPECT_TRUE(it == bksge::end(a));
	}
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};
	test_random_access_range<int> r(a);
	auto iter = r.begin();
	bksge::ranges::advance(iter, 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, 1);
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, -2);
	VERIFY(iter == r.begin());

	bksge::ranges::advance(iter, r.begin() + 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, r.begin());
	VERIFY(iter == r.begin());

	bksge::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, -222, r.begin());
	VERIFY(iter == r.begin());

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[2] ={};
	test_bidirectional_range<int> r(a);
	auto iter = r.begin();
	bksge::ranges::advance(iter, 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, 1);
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, -2);
	VERIFY(iter == r.begin());

	auto iter1 = r.begin();
	++iter1;
	bksge::ranges::advance(iter, iter1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, r.begin());
	VERIFY(iter == r.begin());

	bksge::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, -222, r.begin());
	VERIFY(iter == r.begin());

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	int a[2] ={};
	test_forward_range<int> r(a);
	auto iter = r.begin();
	bksge::ranges::advance(iter, 1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, 1);
	bksge::ranges::advance(iter, 0);
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, 0);
	VERIFY(iter == r.end());

	auto iter1 = r.begin();
	++iter1;
	bksge::ranges::advance(iter, iter1);
	VERIFY(iter != r.begin());
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, r.end());
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, r.end());
	VERIFY(iter == r.end());

	bksge::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	iter = r.begin();
	bksge::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, 99, r.end());
	VERIFY(iter == r.end());

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	int a[2] ={};
	test_input_range<int> r(a);
	auto iter = r.begin();
	bksge::ranges::advance(iter, 1);
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, 1);
	bksge::ranges::advance(iter, 0);
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, 0);
	VERIFY(iter == r.end());

	test_input_range<int> r2(a);
	iter = r2.begin();
	++iter;
	const auto iter1 = iter;
	bksge::ranges::advance(iter, iter1);
	VERIFY(iter == iter1);
	VERIFY(iter != r2.end());
	bksge::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());
	bksge::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());

	bksge::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());
	bksge::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());

	test_input_range<int> r3(a);
	iter = r3.begin();
	bksge::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());
	bksge::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	int a[2] ={};
	test_output_range<int> r(a);
	auto iter = r.begin();
	bksge::ranges::advance(iter, 1);
	VERIFY(iter != r.end());
	bksge::ranges::advance(iter, 1);
	bksge::ranges::advance(iter, 0);
	VERIFY(iter == r.end());
	bksge::ranges::advance(iter, 0);
	VERIFY(iter == r.end());

	test_output_range<int> r2(a);
	iter = r2.begin();
	++iter;
	bksge::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());
	bksge::ranges::advance(iter, r2.end());
	VERIFY(iter == r2.end());

	bksge::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());
	bksge::ranges::advance(iter, 99, r2.end());
	VERIFY(iter == r2.end());

	test_output_range<int> r3(a);
	iter = r3.begin();
	bksge::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());
	bksge::ranges::advance(iter, 99, r3.end());
	VERIFY(iter == r3.end());

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, RangesAdvanceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace advance_test

}	// namespace bksge_iterator_test
