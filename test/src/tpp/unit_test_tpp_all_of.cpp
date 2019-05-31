/**
 *	@file	unit_test_tpp_all_of.cpp
 *
 *	@brief	all_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tpp/all_of.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#define BKSGE_10_Ts		\
	t, t, t, t, t, t, t, t, t, t

#define BKSGE_100_Ts	\
	BKSGE_10_Ts, BKSGE_10_Ts, BKSGE_10_Ts, BKSGE_10_Ts, BKSGE_10_Ts, \
	BKSGE_10_Ts, BKSGE_10_Ts, BKSGE_10_Ts, BKSGE_10_Ts, BKSGE_10_Ts

#define BKSGE_500_Ts	\
	BKSGE_100_Ts, BKSGE_100_Ts, BKSGE_100_Ts, BKSGE_100_Ts, BKSGE_100_Ts

GTEST_TEST(TppTest, AllOfTest)
{
	{
		BKSGE_CONSTEXPR bool t = true;
		BKSGE_CONSTEXPR bool f = false;

		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of());
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of(t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of(t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, f, f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, t, f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, f, f));

		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of(t, t, t, t, t, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, t, t, t, t, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, f, t, t, t, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, f, t, t, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, f, t, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, t, f, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, t, t, f, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, t, t, t, f, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, t, t, t, t, f, t, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, t, t, t, t, t, f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(t, t, t, t, t, t, t, t, t, f));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(f, f, f, f, f, f, f, f, f, f));

		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of(BKSGE_100_Ts, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(BKSGE_100_Ts, f));

		//BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::all_of(BKSGE_500_Ts, t));
		//BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::all_of(BKSGE_500_Ts, f));
	}
}

#undef BKSGE_10_Ts
#undef BKSGE_100_Ts
#undef BKSGE_500_Ts
