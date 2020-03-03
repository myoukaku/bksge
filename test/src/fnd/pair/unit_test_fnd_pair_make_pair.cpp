/**
 *	@file	unit_test_fnd_pair_make_pair.cpp
 *
 *	@brief	make_pair のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/make_pair.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <string>
#include <gtest/gtest.h>

GTEST_TEST(PairTest, MakePairTest)
{
	using bksge::is_same;

	{
		auto const p = bksge::make_pair(0, 1);
		using Pair = decltype(p);
		static_assert(is_same<Pair::first_type, int>::value, "");
		static_assert(is_same<Pair::second_type, int>::value, "");
		EXPECT_EQ(0, p.first);
		EXPECT_EQ(1, p.second);
	}
	{
		auto const p = bksge::make_pair(0.5f, std::string("foo"));
		using Pair = decltype(p);
		static_assert(is_same<Pair::first_type, float>::value, "");
		static_assert(is_same<Pair::second_type, std::string>::value, "");
		EXPECT_EQ(0.5f, p.first);
		EXPECT_EQ("foo", p.second);
	}
}
