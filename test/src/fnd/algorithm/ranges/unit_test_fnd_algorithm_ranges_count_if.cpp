/**
 *	@file	unit_test_fnd_algorithm_ranges_count_if.cpp
 *
 *	@brief	ranges::count_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/count_if.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_count_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int i) const
	{
		return i % 2 == 0;
	}
};

struct IsOdd
{
	constexpr bool operator()(int i) const
	{
		return i % 2 == 1;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	int x[] = { 3,1,4,1,5,9,2,6 };

	VERIFY(ranges::count_if(x, IsEven{}) == 3);
	VERIFY(ranges::count_if(x, IsOdd{})  == 5);

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {11}, {2} };
	auto res = ranges::count_if(x, x+7, [](int i) { return i % 2 == 0; }, &X::i);
	VERIFY(res == 6);
	res = ranges::count_if(x, x+7, [](int i) { return i % 2 == 1; }, &X::i);
	VERIFY(res == 1);
	res = ranges::count_if(x, x+7, [](int i) { return i < 0; }, &X::i);
	VERIFY(res == 0);

	test_range<X, forward_iterator_wrapper> c(x);
	res = ranges::count_if(c, [](int i) { return i == 2; }, &X::i);
	VERIFY(res == 3);
	res = ranges::count_if(c, [](int i) { return i < 0; }, &X::i);
	VERIFY(res == 0);

	test_range<X, input_iterator_wrapper> r(x);
	res = ranges::count_if(c, [](int i) { return i == 2; }, &X::i);
	VERIFY(res == 3);
	res = ranges::count_if(c, [](int i) { return i < 0; }, &X::i);
	VERIFY(res == 0);

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = bksge::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6}, {1,6} };
	VERIFY(ranges::count_if(y, [](int i) { return i <  5; }, &Y::j) == 2);
	VERIFY(ranges::count_if(y, [](int i) { return i != 4; }, &Y::j) == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCountIfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_count_if_test

}	// namespace bksge_algorithm_test
