/**
 *	@file	unit_test_fnd_algorithm_ranges_is_permutation.cpp
 *
 *	@brief	ranges::is_permutation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/is_permutation.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_is_permutation_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	int x[] = { 2, 2, 6,  8, 10, 11 };
	int y[] = { 2, 6, 8, 10, 11,  2 };
	int z[] = { 2, 6, 8, 10,  2,  2 };

	VERIFY( ranges::is_permutation(x, x+6, y, y+6));
	VERIFY(!ranges::is_permutation(x, x+6, y, y+5));

	test_range<int, forward_iterator_wrapper> rx(x), ry(y), rz(z);
	VERIFY( ranges::is_permutation(rx, ry));
	VERIFY(!ranges::is_permutation(rx, rz));

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X   x[] = { {2}, {2}, {6}, { 8}, {10}, {11} };
		X   y[] = { {2}, {6}, {8}, {10}, {11}, { 2} };
		int z[] = { 2, 6, 8, 10, 2, 2 };
		VERIFY( ranges::is_permutation(x, y, {}, &X::i, &X::i));
		VERIFY(!ranges::is_permutation(x, z, {}, &X::i));
		VERIFY(!ranges::is_permutation(z, y, {}, {}, &X::i));
	}
	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;
	{
		std::vector<int> x{};
		std::vector<int> y{};
		VERIFY(ranges::is_permutation(x, y));
	}
	{
		std::vector<int> x{1,2,3};
		std::vector<int> y{2,3,1};
		VERIFY(ranges::is_permutation(x, y));
	}
	{
		std::vector<int> x{1,2,3};
		std::vector<int> y{1,2};
		VERIFY(!ranges::is_permutation(x, y));
	}
	{
		std::forward_list<int> x{};
		std::forward_list<int> y{};
		VERIFY(ranges::is_permutation(x, y));
	}
	{
		std::forward_list<int> x{1,2,3};
		std::forward_list<int> y{2,3,1};
		VERIFY(ranges::is_permutation(x, y));
	}
	{
		std::forward_list<int> x{1,2,3};
		std::forward_list<int> y{1,2};
		VERIFY(!ranges::is_permutation(x, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesIsPermutationTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_is_permutation_test

}	// namespace bksge_algorithm_test
