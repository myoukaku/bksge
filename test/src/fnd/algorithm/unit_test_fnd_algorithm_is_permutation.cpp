/**
 *	@file	unit_test_fnd_algorithm_is_permutation.cpp
 *
 *	@brief	is_permutation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/is_permutation.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <list>
#include <vector>
#include <array>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace is_permutation_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return x == y;
}

GTEST_TEST(AlgorithmTest, IsPermutationTest)
{
	{
		BKSGE_CONSTEXPR_OR_CONST int a[] { 1, 2, 3 };
		BKSGE_CONSTEXPR_OR_CONST int b[] { 1, 2, 3 };
		BKSGE_CONSTEXPR_OR_CONST int c[] { 2, 3, 1 };
		BKSGE_CONSTEXPR_OR_CONST int d[] { 3, 1, 2 };
		BKSGE_CONSTEXPR_OR_CONST int e[] { 1, 2, 4 };
		BKSGE_CONSTEXPR_OR_CONST int f[] { 3, 2, 3 };

		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(a)));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), pred1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::equal_to<>()));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(d)));
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(e)));
		BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(f), pred1));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 4> a {{ 4, 5, 6, 7 }};
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 4> b {{ 6, 4, 5, 7 }};
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 4> c {{ 6, 4, 7, 5 }};
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 4> d {{ 6, 4, 5, 4 }};
		BKSGE_CONSTEXPR_OR_CONST std::array<int, 4> e {{ 4, 5, 6, 8 }};

		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(a), bksge::end(a)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::equal_to<>()));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c)));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(d), bksge::end(d), pred1));
		BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(e), bksge::end(e), bksge::equal_to<>()));
	}
	{
		const std::vector<int> a { 1, 2, 3 };
		const std::vector<int> b { 2, 3, 1 };
		const std::vector<int> c { 2, 3, 4 };

		EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), pred1));
		EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), pred1));
	}
	{
		const std::list<int> a { 3, 2, 1 };
		const std::list<int> b { 2, 3, 1 };
		const std::list<int> c { 2, 3, 4 };

		EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b)));
		EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c)));
		EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::equal_to<>()));
		EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::equal_to<>()));
		EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b)));
		EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c)));
		EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::equal_to<>()));
		EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c), bksge::equal_to<>()));
	}
	{
		const std::string a = "abc";
		const std::string b = "cba";
		const std::string c = "aba";

		EXPECT_TRUE (bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::end(b), bksge::equal_to<>()));
		EXPECT_FALSE(bksge::is_permutation(bksge::begin(a), bksge::end(a), bksge::begin(c), bksge::end(c), bksge::equal_to<>()));
	}
}

}	// namespace is_permutation_test

}	// namespace bksge_algorithm_test
