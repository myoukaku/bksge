/**
 *	@file	unit_test_fnd_iterator_next.cpp
 *
 *	@brief	next のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146); // 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。
BKSGE_WARNING_DISABLE_MSVC(4307); // '+': 整数定数がオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4308); // 負の整数定数が符号なしの型に変換されました。

#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <array>
#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_iterator_test
{

namespace next_test
{

GTEST_TEST(IteratorTest, NextTest)
{
	{
		int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		it = bksge::next(it);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(2, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		const int a[] = {0,1,2};

		auto it = bksge::begin(a);
		EXPECT_EQ(0, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, -1);
		EXPECT_EQ(1, *it);
		it = bksge::next(it, 2);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] = {0, 1, 2, 3, 4};

		BKSGE_CONSTEXPR auto it1 = bksge::begin(a);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, *it1);
		BKSGE_CONSTEXPR auto it2 = bksge::next(it1);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, *it2);
		BKSGE_CONSTEXPR auto it3 = bksge::next(it2, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, *it3);
		BKSGE_CONSTEXPR auto it4 = bksge::next(it3, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it4);
		BKSGE_CONSTEXPR auto it5 = bksge::next(it4, 3);
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == bksge::end(a));
	}
	{
		const std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		it = bksge::next(it);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(4, *it);
		it = bksge::next(it);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(5, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::begin(v);
		EXPECT_EQ(3, *it);
		it = bksge::next(it, 3);
		EXPECT_EQ(1, *it);
		it = bksge::next(it, -1);
		EXPECT_EQ(4, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(5, *it);
		it = bksge::next(it, -4);
		EXPECT_EQ(3, *it);
		it = bksge::next(it, 5);
		EXPECT_TRUE(it == bksge::end(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		it = bksge::next(it);
		EXPECT_EQ(3, *it);
		it = bksge::next(it);
		EXPECT_EQ(4, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		const std::list<int> l {2, 3, 4};

		auto it = bksge::begin(l);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(4, *it);
		it = bksge::next(it, -2);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, 3);
		EXPECT_TRUE(it == bksge::end(l));
	}
	{
		const std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		it = bksge::next(it);
		EXPECT_EQ(2, *it);
		it = bksge::next(it);
		EXPECT_EQ(3, *it);
		it = bksge::next(it);
		EXPECT_EQ(4, *it);
		it = bksge::next(it);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::begin(a);
		EXPECT_EQ(1, *it);
		it = bksge::next(it, 2);
		EXPECT_EQ(3, *it);
		it = bksge::next(it, -1);
		EXPECT_EQ(2, *it);
		it = bksge::next(it, 3);
		EXPECT_TRUE(it == bksge::end(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<float, 4> a{{1, 2, 3, 4}};

		BKSGE_CXX17_CONSTEXPR auto it1 = bksge::begin(a);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it1);
		BKSGE_CXX17_CONSTEXPR auto it2 = bksge::next(it1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CXX17_CONSTEXPR auto it3 = bksge::next(it2, 2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, *it3);
		BKSGE_CXX17_CONSTEXPR auto it4 = bksge::next(it3, -1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CXX17_CONSTEXPR auto it5 = bksge::next(it4, 2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == bksge::end(a));

		BKSGE_CXX17_CONSTEXPR auto d = bksge::end(a) - bksge::begin(a);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, d);
	}
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_random_access_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = bksge::ranges::next(begin, end);
	VERIFY(*bksge::ranges::next(begin) == 1);
	VERIFY( bksge::ranges::next(begin, 0) == begin);
	VERIFY(*bksge::ranges::next(begin, 1) == 1);
	VERIFY(*bksge::ranges::next(begin, 3) == 3);
	VERIFY(*bksge::ranges::next(endi, -4) == 6);
	VERIFY( bksge::ranges::next(begin, begin) == begin);
	VERIFY( bksge::ranges::next(begin, end) == end);
	VERIFY( bksge::ranges::next(endi, end) == end);
	VERIFY( bksge::ranges::next(endi, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 0, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 5, begin) == begin);
	VERIFY( bksge::ranges::next(begin, -5, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 0, end) == begin);
	VERIFY(*bksge::ranges::next(begin, 5, end) == 5);
	VERIFY( bksge::ranges::next(begin, 55, end) == end);
	VERIFY( bksge::ranges::next(endi, 0, end) == end);
	VERIFY( bksge::ranges::next(endi, -5, end) == end);
	VERIFY( bksge::ranges::next(endi, -55, end) == end);
	VERIFY( bksge::ranges::next(endi, 0, begin) == end);
	VERIFY(*bksge::ranges::next(endi, -5, begin) == 5);
	VERIFY( bksge::ranges::next(endi, -55, begin) == begin);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_bidirectional_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = bksge::ranges::next(begin, end);
	VERIFY(*bksge::ranges::next(begin) == 1);
	VERIFY( bksge::ranges::next(begin, 0) == begin);
	VERIFY(*bksge::ranges::next(begin, 1) == 1);
	VERIFY(*bksge::ranges::next(begin, 3) == 3);
	VERIFY(*bksge::ranges::next(endi, -4) == 6);
	VERIFY( bksge::ranges::next(begin, begin) == begin);
	VERIFY( bksge::ranges::next(begin, end) == end);
	VERIFY( bksge::ranges::next(endi, end) == end);
	VERIFY( bksge::ranges::next(endi, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 0, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 5, begin) == begin);
	VERIFY( bksge::ranges::next(begin, -5, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 0, end) == begin);
	VERIFY(*bksge::ranges::next(begin, 5, end) == 5);
	VERIFY( bksge::ranges::next(begin, 55, end) == end);
	VERIFY( bksge::ranges::next(endi, 0, end) == end);
	VERIFY( bksge::ranges::next(endi, -5, end) == end);
	VERIFY( bksge::ranges::next(endi, -55, end) == end);
	VERIFY( bksge::ranges::next(endi, 0, begin) == end);
	VERIFY(*bksge::ranges::next(endi, -5, begin) == 5);
	VERIFY( bksge::ranges::next(endi, -55, begin) == begin);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_forward_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = bksge::ranges::next(begin, end);
	VERIFY(*bksge::ranges::next(begin) == 1);
	VERIFY( bksge::ranges::next(begin, 0) == begin);
	VERIFY(*bksge::ranges::next(begin, 1) == 1);
	VERIFY(*bksge::ranges::next(begin, 3) == 3);
	VERIFY( bksge::ranges::next(begin, begin) == begin);
	VERIFY( bksge::ranges::next(begin, end) == end);
	VERIFY( bksge::ranges::next(endi, end) == end);
	VERIFY( bksge::ranges::next(begin, 0, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 5, begin) == begin);
	VERIFY( bksge::ranges::next(begin, -5, begin) == begin);
	VERIFY( bksge::ranges::next(begin, 0, end) == begin);
	VERIFY(*bksge::ranges::next(begin, 5, end) == 5);
	VERIFY( bksge::ranges::next(begin, 55, end) == end);
	VERIFY( bksge::ranges::next(endi, 0, end) == end);
	VERIFY( bksge::ranges::next(endi, 5, end) == end);
	VERIFY( bksge::ranges::next(endi, 55, end) == end);
	VERIFY( bksge::ranges::next(endi, 0, begin) == end);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_input_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto iter = bksge::ranges::next(begin);
	VERIFY(*iter == 1);
	iter = bksge::ranges::next(iter, 0);
	VERIFY(*iter == 1);
	iter = bksge::ranges::next(iter, 1);
	VERIFY(*iter == 2);
	iter = bksge::ranges::next(iter, 4);
	VERIFY(*iter == 6);

	iter = bksge::ranges::next(iter, iter);
	VERIFY(*iter == 6);
	iter = bksge::ranges::next(iter, end);
	VERIFY(iter == end);
	iter = bksge::ranges::next(iter, end);
	VERIFY(iter == end);

	test_input_range<int> r2(a);
	begin = r2.begin();
	end = r2.end();
	auto endi = bksge::ranges::next(begin, end);
	// reset single-pass input range
	r2.m_first = a;
	iter = bksge::ranges::next(begin, 0, begin);
	VERIFY(*iter == 0);
	iter = bksge::ranges::next(begin, 5, begin);
	VERIFY(*iter == 0);
	iter = bksge::ranges::next(begin, -5, begin);
	VERIFY(*iter == 0);
	iter = bksge::ranges::next(begin, 0, end);
	VERIFY(*iter == 0);
	iter = bksge::ranges::next(endi, 0, begin);
	VERIFY(iter == end);
	iter = bksge::ranges::next(begin, 5, end); // invalidates begin
	VERIFY(*iter == 5);
	iter = bksge::ranges::next(iter, 55, end);
	VERIFY(iter == end);
	iter = bksge::ranges::next(endi, 0, end);
	VERIFY(iter == end);
	iter = bksge::ranges::next(endi, 5, end);
	VERIFY(iter == end);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_output_range<int> r(a);
	auto iter = r.begin();
	auto end = r.end(); // sentinel, !same_as<decltype(iter), decltype(end)>

	iter = bksge::ranges::next(iter);
	*iter = 10;
	VERIFY(a[1] == 10);
	iter = bksge::ranges::next(iter, 0);
	iter = bksge::ranges::next(iter, 1);
	*iter = 20;
	VERIFY(a[2] == 20);
	iter = bksge::ranges::next(iter, 4);
	iter = bksge::ranges::next(iter, 0);
	*iter = 60;
	VERIFY(a[6] == 60);

	iter = bksge::ranges::next(iter, end);
	VERIFY(iter == end);
	iter = bksge::ranges::next(iter, end);
	VERIFY(iter == end);

	test_output_range<int> r2(a);
	iter = bksge::ranges::next(r2.begin(), 5);
	end = r2.end();

	iter = bksge::ranges::next(iter, 0, end);
	*iter = 50;
	VERIFY(a[5] == 50);
	iter = bksge::ranges::next(iter, 2, end);
	*iter = 70;
	VERIFY(a[7] == 70);
	iter = bksge::ranges::next(iter, 5, end);
	VERIFY(iter == end);

	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, RangesNextTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace next_test

}	// namespace bksge_iterator_test

BKSGE_WARNING_POP();
