/**
 *	@file	unit_test_fnd_algorithm_ranges_mismatch.cpp
 *
 *	@brief	ranges::mismatch のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/mismatch.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_mismatch_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		int y[] = { 1,2,0,4,5 };
		auto res = ranges::mismatch(x, y);
		VERIFY(res.in1 == x+2 && res.in2 == y+2);
	}
	{
		int x[] = { 1,2,3,4,5 };
		int y[] = { 1,2,3,4,5 };
		auto res = ranges::mismatch(x, y);
		VERIFY(res.in1 == x+5 && res.in2 == y+5);
	}
	{
		int x[] = { 1,2,3,4,5 };
		int y[] = { 1,2,3,4 };
		auto res = ranges::mismatch(x, y);
		VERIFY(res.in1 == x+4 && res.in2 == y+4);
	}
	{
		int x[] = { 2,2,3,4,5 };
		int y[] = { 1,2,3,4 };
		auto res = ranges::mismatch(x, y);
		VERIFY(res.in1 == x+0 && res.in2 == y+0);
	}

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = bksge::ranges;

	X xa[] = { {1}, {2}, {3}, {4}, {5}, {6} };
	X xb[] = { {1}, {2}, {3}, {3}, {5}, {6} };
	auto res = ranges::mismatch(xa, xa+6, xb, xb+6, {}, &X::i, &X::i);
	VERIFY(res.in1 == xa+3 && res.in2 == xb+3);

	test_range<X, forward_iterator_wrapper> ca(xa);
	test_range<X, forward_iterator_wrapper> cb(xb);
	auto res2 = ranges::mismatch(ca, cb, {}, &X::i, &X::i);
	VERIFY((*res2.in1).i == 4 && (*res2.in2).i == 3);
	res2 = ranges::mismatch(ca, ca, {}, &X::i, &X::i);
	VERIFY(res2.in1 == ranges::end(ca) && res2.in2 == ranges::end(ca));

	test_range<X, input_iterator_wrapper> ra(xa);
	test_range<X, input_iterator_wrapper> rb(xb);
	auto res3 = ranges::mismatch(ra, rb, {}, &X::i, &X::i);
	VERIFY((*res3.in1).i == 4 && (*res3.in2).i == 3);

	test_range<X, input_iterator_wrapper> ra2(xa);
	test_range<X, input_iterator_wrapper> ra3(xa);
	res3 = ranges::mismatch(ra2, ra3, {}, &X::i, &X::i);
	VERIFY(res3.in1 == ranges::end(ra2) && res3.in2 == ranges::end(ra3));

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = bksge::ranges;

	Y ya[] = { {1,2}, {2,4}, {3,6}, {1,6} };
	Y yb[] = { {2,1}, {4,2}, {4,2}, {7,1} };
	VERIFY(ranges::mismatch(ya, yb, {}, &Y::i, &Y::j).in1 == ya+2);
	VERIFY(ranges::mismatch(ya, yb, {}, &Y::i, &Y::j).in2 == yb+2);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMismatchTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_mismatch_test

}	// namespace bksge_algorithm_test
