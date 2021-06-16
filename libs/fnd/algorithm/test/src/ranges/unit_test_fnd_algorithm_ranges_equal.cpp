/**
 *	@file	unit_test_fnd_algorithm_ranges_equal.cpp
 *
 *	@brief	ranges::equal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X { int i; };

struct Proj
{
	BKSGE_CONSTEXPR int operator()(int t) const BKSGE_NOEXCEPT
	{
		return t+1;
	}
};

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int x[] = { 2, 2, 6, 8, 10, 11, 11 };
	int y[] = { 2, 2, 6, 8, 10, 11, 11 };
	int z[] = { 3, 3, 7, 9, 11, 12, 12 };

	test_range<int, forward_iterator_wrapper> cx(x);
	test_range<int, forward_iterator_wrapper> cy(y);
	test_range<int, forward_iterator_wrapper> cz(z);
	VERIFY( bksge::ranges::equal(cx, cy));
	VERIFY(!bksge::ranges::equal(cx, cy, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cy, {}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cz));
	VERIFY( bksge::ranges::equal(cx, cz, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cz, {}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cy, bksge::ranges::greater{}));
	VERIFY(!bksge::ranges::equal(cx, cy, bksge::ranges::less{}));
	VERIFY( bksge::ranges::equal(cx, cy, bksge::ranges::greater{}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cy, bksge::ranges::less{},    Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cy, bksge::ranges::greater{}, {}, Proj{}));
	VERIFY( bksge::ranges::equal(cx, cy, bksge::ranges::less{},    {}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cz, bksge::ranges::greater{}));
	VERIFY( bksge::ranges::equal(cx, cz, bksge::ranges::less{}));

	test_range<int, input_iterator_wrapper> rx(x);
	test_range<int, input_iterator_wrapper> ry(y);
	test_range<int, input_iterator_wrapper> rz(z);
	VERIFY( bksge::ranges::equal(rx, ry));
	VERIFY(!bksge::ranges::equal(rx, ry, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(rx, ry, {}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(rx, rz));
	VERIFY( bksge::ranges::equal(rx, rz, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(rx, rz, {}, {}, Proj{}));

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int x[] = { 1, 2, 3, 4, 5 };
	int y[] = { 1, 2, 3, 4, 5 };
	int z[] = { 1, 2, 3, 4, 5, 6 };
	int w[] = { 1, 2, 3, 4 };

	VERIFY( bksge::ranges::equal(x, y));
	VERIFY(!bksge::ranges::equal(x, z));
	VERIFY(!bksge::ranges::equal(x, w));
	VERIFY(!bksge::ranges::equal(x, y, bksge::ranges::greater{}));
	VERIFY(!bksge::ranges::equal(x, z, bksge::ranges::greater{}));
	VERIFY(!bksge::ranges::equal(x, w, bksge::ranges::greater{}));
	VERIFY(!bksge::ranges::equal(x, y, bksge::ranges::less{}));
	VERIFY(!bksge::ranges::equal(x, z, bksge::ranges::less{}));
	VERIFY(!bksge::ranges::equal(x, w, bksge::ranges::less{}));
	VERIFY( bksge::ranges::equal(x, y, bksge::ranges::greater{}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, z, bksge::ranges::greater{}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, w, bksge::ranges::greater{}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, y, bksge::ranges::less{}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, z, bksge::ranges::less{}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, w, bksge::ranges::less{}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, y, bksge::ranges::greater{}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, z, bksge::ranges::greater{}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, w, bksge::ranges::greater{}, {}, Proj{}));
	VERIFY( bksge::ranges::equal(x, y, bksge::ranges::less{}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, z, bksge::ranges::less{}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(x, w, bksge::ranges::less{}, {}, Proj{}));

	return true;
}

bool test03()
{
	int x[] = { 2, 2, 6, 8, 10, 11, 11 };
	int y[] = { 2, 2, 6, 8, 10, 11, 11 };
	X   z[] = { {2}, {6}, {8}, {10}, {2}, {2} };
	int w[] = { 1, 1, 1, 1, 1 };

	VERIFY(bksge::ranges::equal(w, w + 4, w + 1, w + 5));
	VERIFY(bksge::ranges::equal(w, w + 5, w, w + 5, bksge::ranges::greater{}, Proj{}));

	test_range<int, forward_iterator_wrapper> cx(x), cy(y);
	test_range<X, forward_iterator_wrapper> cz(z);
	VERIFY(bksge::ranges::equal(cx, cy));
	VERIFY(!bksge::ranges::equal(cx, cy, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(cx, cz, {}, {}, &X::i));

	test_range<int, input_iterator_wrapper> rx(x), ry(y);
	test_range<X, input_iterator_wrapper> rz(z);
	VERIFY(bksge::ranges::equal(rx, ry));

	rx.m_first = x;
	ry.m_first = y;
	VERIFY(!bksge::ranges::equal(rx, ry, {}, {}, Proj{}));

	rx.m_first = x;
	rz.m_first = z;
	VERIFY(!bksge::ranges::equal(rx, rz, {}, {}, &X::i));

	return true;
}

bool test04()
{
	X   x[] = { {2}, {2}, {6}, { 8}, {10}, {11} };
	X   y[] = { {2}, {6}, {8}, {10}, {11}, { 2} };
	int z[] = { 2, 6, 8, 10, 2, 2 };
	int w[] = { 2, 6, 8, 10, 2, 2 };

	VERIFY(bksge::ranges::equal(z, w));
	VERIFY(bksge::ranges::equal(z, w, {}));
	VERIFY(!bksge::ranges::equal(z, w, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(z, w, {}, {}, Proj{}));
	VERIFY(!bksge::ranges::equal(z, z + 5, w + 1, w + 6));
	VERIFY(!bksge::ranges::equal(z, z + 5, w + 1, w + 5));
	VERIFY(!bksge::ranges::equal(x, y, {}, &X::i, &X::i));
	VERIFY(bksge::ranges::equal(x + 1, x + 5, y, y + 4, {}, &X::i, &X::i));

	return true;
}

bool test05()
{
	bksge::vector<int> x = {2, 2, 6, 8, 10, 11};
	bksge::vector<int> y = {2, 2, 6, 8, 10, 11};
	bksge::vector<int> z = {2, 2, 6, 8, 10, 12};
	VERIFY( bksge::ranges::equal(x, y));
	VERIFY(!bksge::ranges::equal(x, z));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesEqualTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
	EXPECT_TRUE(test05());
}

}	// namespace ranges_equal_test

}	// namespace bksge_algorithm_test
