/**
 *	@file	unit_test_fnd_pair_get.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/get.hpp>
#include <bksge/fnd/pair/make_pair.hpp>
//#include <bksge/fnd/tuple/get.hpp>
#include <tuple>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(PairTest, GetTest)
{
	{
		const bksge::pair<int, std::string> p(1, "Foo");
		EXPECT_EQ(1,     bksge::get<0>(p));
		EXPECT_EQ("Foo", bksge::get<1>(p));
	}
	//{
	//	const std::pair<int, std::string> p(1, "Foo");
	//	EXPECT_EQ(1,     bksge::get<0>(p));
	//	EXPECT_EQ("Foo", bksge::get<1>(p));
	//}
	{
		BKSGE_CONSTEXPR bksge::pair<double, int> p(3.5, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(3.5, bksge::get<0>(p));
		BKSGE_CONSTEXPR_EXPECT_EQ(4,   bksge::get<1>(p));
	}
	{
		BKSGE_CONSTEXPR_EXPECT_EQ(1,   bksge::get<0>(bksge::make_pair(1, 0.5)));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.5, bksge::get<1>(bksge::make_pair(1, 0.5)));
	}
	{
		bksge::pair<int, float> p;
		bksge::get<0>(p) = 4;
		bksge::get<1>(p) = 5.5f;
		EXPECT_EQ(4,    p.first);
		EXPECT_EQ(5.5f, p.second);
	}
}
