/**
 *	@file	unit_test_fnd_algorithm_mismatch.cpp
 *
 *	@brief	mismatch のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/mismatch.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/list.hpp>
#include <vector>
#include <gtest/gtest.h>
#include <array>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace mismatch_test
{

BKSGE_CONSTEXPR bool pred1(int x, int y)
{
	return (x % 2) == (y % 2);
}

GTEST_TEST(AlgorithmTest, MismatchTest)
{
	{
		BKSGE_STATIC_CONSTEXPR int a1[] = { 1,2,3 };
		BKSGE_STATIC_CONSTEXPR int a2[] = { 1,2,3 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto p =
			bksge::mismatch(bksge::begin(a1), bksge::end(a1), bksge::begin(a2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == bksge::end(a1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == bksge::end(a2));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a1[] = { 1,2,3 };
		BKSGE_STATIC_CONSTEXPR int a2[] = { 1,2,3,4 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto p =
			bksge::mismatch(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == bksge::end(a1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == bksge::next(bksge::begin(a2), 3));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a1[] = { 1,2,3,4 };
		BKSGE_STATIC_CONSTEXPR int a2[] = { 1,2,3 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto p =
			bksge::mismatch(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == bksge::next(bksge::begin(a1), 3));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == bksge::end(a2));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a1[] = { 1,2,3,4,5 };
		BKSGE_STATIC_CONSTEXPR int a2[] = { 1,2,5,6,4 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto p =
			bksge::mismatch(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == bksge::next(bksge::begin(a1), 4));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == bksge::next(bksge::begin(a2), 4));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a1[] = { 1,2,3,4,5 };
		BKSGE_STATIC_CONSTEXPR int a2[] = { 1,2,5,6,4 };
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto p =
			bksge::mismatch(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2), pred1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.first  == bksge::next(bksge::begin(a1), 4));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(p.second == bksge::next(bksge::begin(a2), 4));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int, 6> a1 ={{ 1,2,3,4,5,6 }};
		BKSGE_STATIC_CONSTEXPR int a2[]                = { 1,2,3,1,5 };
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto p =
			bksge::mismatch(bksge::begin(a1), bksge::end(a1), bksge::begin(a2));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(p.first  == bksge::next(bksge::begin(a1), 3));
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(p.second == bksge::next(bksge::begin(a2), 3));
	}
	{
		const std::vector<int>     v = { 1,2,3,4,3,2 };
		const std::array<int, 6> a ={{ 1,2,4,3,2,1 }};
		auto const p = bksge::mismatch(bksge::begin(v), bksge::end(v), bksge::begin(a));
		EXPECT_TRUE(p.first  == bksge::next(bksge::begin(v), 2));
		EXPECT_TRUE(p.second == bksge::next(bksge::begin(a), 2));
	}
	{
		const bksge::list<int>   l = { 1,2,3,4,3, };
		const std::vector<int> v = { 1,2,3,4,3,2 };
		auto const p = bksge::mismatch(bksge::begin(l), bksge::end(l), bksge::begin(v));
		EXPECT_TRUE(p.first  == bksge::end(l));
		EXPECT_TRUE(p.second == bksge::next(bksge::begin(v), 5));
	}
	{
		const bksge::list<int>   l = { 1,2,3,4,5 };
		const std::vector<int> v = { 3,4,3,3,5 };
		auto const p = bksge::mismatch(bksge::begin(l), bksge::end(l), bksge::begin(v), pred1);
		EXPECT_TRUE(p.first  == bksge::next(bksge::begin(l), 3));
		EXPECT_TRUE(p.second == bksge::next(bksge::begin(v), 3));
	}
	{
		const bksge::list<int>   l = { 1,2,3,4,5 };
		const std::vector<int> v = { 1,2,3,4 };
		auto const p = bksge::mismatch(bksge::begin(l), bksge::end(l), bksge::begin(v), bksge::end(v));
		EXPECT_TRUE(p.first  == bksge::next(bksge::begin(l), 4));
		EXPECT_TRUE(p.second == bksge::end(v));
	}
	{
		const bksge::list<int>   l = { 1,2,3,4 };
		const std::vector<int> v = { 1,2,3,4,5 };
		auto const p = bksge::mismatch(bksge::begin(l), bksge::end(l), bksge::begin(v), bksge::end(v), [](int x, int y) { return x == y; });
		EXPECT_TRUE(p.first  == bksge::end(l));
		EXPECT_TRUE(p.second == bksge::next(bksge::begin(v), 4));
	}
}

}	// namespace mismatch_test

}	// namespace bksge_algorithm_test
