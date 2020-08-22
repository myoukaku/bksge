/**
 *	@file	unit_test_fnd_algorithm_ranges_for_each.cpp
 *
 *	@brief	ranges::for_each のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/for_each.hpp>
#include <bksge/fnd/functional/ref.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_for_each_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X { int i; };

BKSGE_CXX14_CONSTEXPR void f(int& i)
{
	i += 1;
}

struct Foo
{
	int a = 0;

	BKSGE_CXX14_CONSTEXPR void operator()(int& i)
	{
		a += i;
	}
};

struct Bar
{
	int a = 0;

	BKSGE_CXX14_CONSTEXPR void operator()(X& x)
	{
		a += x.i * 2;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	int x[] = { 1, 3, 4 };

	auto res = ranges::for_each(x, x+3, f);
	VERIFY(res.in == x+3);
	VERIFY(res.fun == &f);

	VERIFY(x[0] == 2);
	VERIFY(x[1] == 4);
	VERIFY(x[2] == 5);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {4}, {6}, {8}, {10}, {11} };

	{
		test_range<X, forward_iterator_wrapper> c(x);
		Bar b;
		ranges::for_each(c, bksge::ref(b));
		VERIFY(b.a == 82);
	}
	{
		test_range<X, input_iterator_wrapper> r(x);
		Bar b;
		ranges::for_each(r, bksge::ref(b));
		VERIFY(b.a == 82);
	}
	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {4}, {6}, {8}, {10}, {11} };

	{
		test_range<X, forward_iterator_wrapper> c(x);
		Foo f;
		ranges::for_each(c, bksge::ref(f), &X::i);
		VERIFY(f.a == 41);
	}
	{
		test_range<X, input_iterator_wrapper> r(x);
		Foo f;
		ranges::for_each(r, bksge::ref(f), &X::i);
		VERIFY(f.a == 41);
	}

	return true;
}

struct Y { int i; int j; };

inline bool test04()
{
	namespace ranges = bksge::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	{
		int a = 0;
		ranges::for_each(y, [&a](int i) { a += i; }, &Y::i);
		VERIFY(a == 6);
	}
	{
		int a = 0;
		ranges::for_each(y, [&a](int i) { a += i; }, &Y::j);
		VERIFY(a == 12);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesForEachTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_for_each_test

}	// namespace bksge_algorithm_test
