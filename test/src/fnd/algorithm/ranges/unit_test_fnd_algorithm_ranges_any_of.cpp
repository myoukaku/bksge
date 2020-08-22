/**
 *	@file	unit_test_fnd_algorithm_ranges_any_of.cpp
 *
 *	@brief	ranges::any_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/any_of.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_any_of_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct ILess
{
	int val;
	constexpr bool operator()(int& i) const { return i < val; }
};

template<typename T>
struct NotZero
{
	constexpr bool operator()(T& t) const { return t != 0; }
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	int x[] = { 2, 4, 6, 8, 10, 11 };

	VERIFY( ranges::any_of(x, x+6, ILess{ 3 }));
	VERIFY(!ranges::any_of(x+1, x+6, ILess{ 3 }));
	VERIFY( ranges::any_of(x, ILess{ 5 }));

	test_range<int, forward_iterator_wrapper> c(x);
	VERIFY( ranges::any_of(c, NotZero<int>{}));

	test_range<int, input_iterator_wrapper> r(x);
	VERIFY( ranges::any_of(r, NotZero<int>{}));

	return true;
}

struct X { int i; };

struct XLess
{
	int val;
	constexpr bool operator()(X& x) const { return x.i < val; }
};

inline bool test02()
{
	namespace ranges = bksge::ranges;

	X x[] = { {2}, {4}, {6}, {8}, {10}, {11} };

	VERIFY( ranges::any_of(x, x+6, XLess{ 3 }));
	VERIFY( ranges::any_of(x, x+6, ILess{ 3 }, &X::i));
	VERIFY(!ranges::any_of(x+1, x+6, XLess{ 3 }));
	VERIFY(!ranges::any_of(x+1, x+6, ILess{ 3 }, &X::i));
	VERIFY( ranges::any_of(x, XLess{ 5 }));
	VERIFY( ranges::any_of(x, ILess{ 5 }, &X::i));

	test_range<X, forward_iterator_wrapper> c(x);
	VERIFY( ranges::any_of(c, NotZero<int>{}, &X::i));

	test_range<X, input_iterator_wrapper> r(x);
	VERIFY( ranges::any_of(r, NotZero<int>{}, &X::i));
	VERIFY( ranges::any_of(r, NotZero<X* const>{}, [](X& x) { return &x; }));

	return true;
}

struct Y { int i; int j; };

inline bool test03()
{
	namespace ranges = bksge::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };

	VERIFY( ranges::any_of(y, [](int i) { return i%2 == 0; }, &Y::i));
	VERIFY( ranges::any_of(y, [](const Y& y) { return y.i + y.j == 3; }));
	VERIFY(!ranges::any_of(y, [](const Y& y) { return y.i == y.j; }));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesAnyOfTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_any_of_test

}	// namespace bksge_algorithm_test
