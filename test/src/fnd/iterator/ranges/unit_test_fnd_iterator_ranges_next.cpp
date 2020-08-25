/**
 *	@file	unit_test_fnd_iterator_ranges_next.cpp
 *
 *	@brief	ranges::next のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_iterator_test
{

namespace ranges_next_test
{

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

}	// namespace ranges_next_test

}	// namespace bksge_iterator_test
