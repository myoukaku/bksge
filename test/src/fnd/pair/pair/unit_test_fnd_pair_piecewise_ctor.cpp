/**
 *	@file	unit_test_fnd_pair_piecewise_ctor.cpp
 *
 *	@brief	pairのpiecewiseコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(PairTest, PiecewiseCtorTest)
{
	{
		typedef bksge::pair<int, int*> P1;
		typedef bksge::pair<int*, int> P2;
		typedef bksge::pair<P1, P2> P3;
		P3 p3(
			std::piecewise_construct,
			bksge::tuple<int, int*>(3, nullptr),
			bksge::tuple<int*, int>(nullptr, 4));
		EXPECT_TRUE(p3.first == P1(3, nullptr));
		EXPECT_TRUE(p3.second == P2(nullptr, 4));
	}
#if !(defined(_MSC_VER) && (_MSC_VER <= 1900))
	{
		typedef bksge::pair<int, float> P1;
		typedef bksge::pair<float, int> P2;
		typedef bksge::pair<P1, P2> P3;
		/*BKSGE_CXX20_CONSTEXPR*/ P3 p3(
			std::piecewise_construct,
			bksge::tuple<int, float>(3, 0.5f),
			bksge::tuple<float, int>(2.5f, 4));
		/*BKSGE_CXX20_CONSTEXPR_*/EXPECT_TRUE(p3.first == P1(3, 0.5f));
		/*BKSGE_CXX20_CONSTEXPR_*/EXPECT_TRUE(p3.second == P2(2.5f, 4));
	}
#endif
}
