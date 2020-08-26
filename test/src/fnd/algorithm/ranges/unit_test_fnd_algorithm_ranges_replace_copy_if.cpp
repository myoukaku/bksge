/**
 *	@file	unit_test_fnd_algorithm_ranges_replace_copy_if.cpp
 *
 *	@brief	ranges::replace_copy_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/replace_copy_if.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_replace_copy_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <int N>
struct Less
{
	constexpr bool operator()(int x) const
	{
		return x < N;
	}
};

template <int N>
struct Greater
{
	constexpr bool operator()(int x) const
	{
		return x > N;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		int w[9] = {};
		auto res = ranges::replace_copy_if(x, x+9, w, Less<5>{}, 0);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+9);
		int const y[] = { 0,0,0,0,5,6,7,8,9 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	{
		int const x[] = { 1,2,3,4,5,6,7,8,9 };
		int w[9] = {};
		auto res = ranges::replace_copy_if(x, x+9, w, Greater<5>{}, 1);
		VERIFY(res.in  == x+9);
		VERIFY(res.out == w+9);
		int const y[] = { 1,2,3,4,5,1,1,1,1 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 3,1,4,1,5,9,2,6,5 };
		int w[9] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::replace_copy_if(rx, rw.begin(), Less<5>{}, 0);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 0,0,0,0,5,9,0,6,5 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	{
		int const x[] = { 3,1,4,1,5,9,2,6,5 };
		int w[9] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::replace_copy_if(rx, rw.begin(), Greater<3>{}, 8);
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 3,1,8,1,8,8,2,8,8 };
		VERIFY(!ranges::equal(x, y));
		VERIFY( ranges::equal(w, y));
	}
	return true;
}

struct X
{
	int i;

	friend constexpr bool
	operator==(const X& a, const X& b)
	{
		return a.i == b.i;
	}

	friend constexpr bool
	operator!=(const X& a, const X& b)
	{
		return !(a == b);
	}
};

struct Y
{
	int i;
	int j;

	friend constexpr bool
	operator==(const Y& a, const Y& b)
	{
		return a.i == b.i && a.j == b.j;
	}

	friend constexpr bool
	operator!=(const Y& a, const Y& b)
	{
		return !(a == b);
	}
};

inline bool test03()
{
	namespace ranges = bksge::ranges;
	{
		X const x[6] = { {1}, {2}, {3}, {4}, {5}, {6} };
		X w[6] = {};
		auto res = ranges::replace_copy_if(x, x+5, w,
			[](int a){return a%2 == 0; }, X{ 9 }, &X::i);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		X const y[6] = { {1}, {9}, {3}, {9}, {5}, {0} };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		Y const x[] = { {1,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy_if(x, w,
			[](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::i);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
		Y const y[] = { {4,5}, {2,4}, {4,5} };
		VERIFY(ranges::equal(w, y));
	}
	{
		Y const x[] = { {1,2}, {2,4}, {3,6} };
		Y w[3] = {};
		auto res = ranges::replace_copy_if(x, w,
			[](int a){return a%2 == 1; }, Y{ 4,5 }, &Y::j);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
		Y const y[] = { {1,2}, {2,4}, {3,6} };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesReplaceCopyIfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_replace_copy_if_test

}	// namespace bksge_algorithm_test
