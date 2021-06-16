/**
 *	@file	unit_test_fnd_algorithm_ranges_transform.cpp
 *
 *	@brief	ranges::transform のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/transform.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_transform_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {3,1,4,1,5};
		int w[5] = {};
		auto res = ranges::transform(x, x + 5, w, bksge::negate<>{});
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		int const y[5] = { -3,-1,-4,-1,-5 };
 		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {3,1,4,1,5};
		int w[5] = {};
		test_range<int, input_iterator_wrapper>  rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::transform(rx, rw.begin(), bksge::negate<>{});
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[5] = { -3,-1,-4,-1,-5 };
 		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {1,2,3,4,5};
		int y[] = {2,4,6,8,10};
		int w[5] = {};
		auto res = ranges::transform(x, x + 5, y, y + 5, w, bksge::plus<>{});
		VERIFY(res.in1 == x+5);
		VERIFY(res.in2 == y+5);
		VERIFY(res.out == w+5);
		int const z[5] = { 3,6,9,12,15 };
 		VERIFY(ranges::equal(w, z));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = {1,2,3,4,5};
		int y[] = {2,4,6,8,10};
		int w[5] = {};
		test_range<int, input_iterator_wrapper>  rx(x);
		test_range<int, input_iterator_wrapper>  ry(y);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::transform(rx, ry, rw.begin(), bksge::plus<>{});
		VERIFY(res.in1 == rx.end());
		VERIFY(res.in2 == ry.end());
		VERIFY(res.out == rw.end());
		int const z[5] = { 3,6,9,12,15 };
 		VERIFY(ranges::equal(w, z));
	}
	return true;
}

struct X { int i; };
struct Y { int i; int j; };

inline bool test05()
{
	namespace ranges = bksge::ranges;
	{
		X x[6] = { {2}, {4}, {6}, {8}, {10}, {11} };
		int w[6] = {};
		auto res = ranges::transform(x, x + 6, w, [](int a) { return a+1; }, &X::i);
		VERIFY(res.in  == x+6);
		VERIFY(res.out == w+6);
		int const y[6] = { 3,5,7,9,11,12 };
 		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test06()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> x {1,2,3,4,5};
		auto res = ranges::transform(x, x.begin(), [](int a) { return a+1; });
		VERIFY(res.in  == x.end());
		VERIFY(res.out == x.end());
		int const y[5] = { 2,3,4,5,6 };
 		VERIFY(ranges::equal(x, y));
	}
	return true;
}

inline bool test07()
{
	namespace ranges = bksge::ranges;
	{
		Y x[] = { {1,2}, {2,4}, {3,6} };
		int w[3] = {};
		auto res = ranges::transform(x, x+3, x, x+3, w,
			[](int a, int b) { return a+b; }, &Y::i, &Y::j);
		VERIFY(res.in1 == x+3);
		VERIFY(res.in2 == x+3);
		VERIFY(res.out == w+3);
		int const y[3] = { 3,6,9, };
 		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test08()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> x {1,2,3,4};
		auto res = ranges::transform(x, x, x.begin(), [](int a, int b) { return a*b; });
		VERIFY(res.in1 == x.end());
		VERIFY(res.in2 == x.end());
		VERIFY(res.out == x.end());
		int const y[4] = { 1,4,9,16 };
 		VERIFY(ranges::equal(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesTransformTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	EXPECT_TRUE(test05());
	EXPECT_TRUE(test06());
	EXPECT_TRUE(test07());
	EXPECT_TRUE(test08());
}

}	// namespace ranges_transform_test

}	// namespace bksge_algorithm_test
