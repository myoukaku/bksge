/**
 *	@file	unit_test_tpp_any_of.cpp
 *
 *	@brief	any_of のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/tpp/any_of.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#define BKSGE_10_Fs		\
	f, f, f, f, f, f, f, f, f, f

#define BKSGE_100_Fs	\
	BKSGE_10_Fs, BKSGE_10_Fs, BKSGE_10_Fs, BKSGE_10_Fs, BKSGE_10_Fs, \
	BKSGE_10_Fs, BKSGE_10_Fs, BKSGE_10_Fs, BKSGE_10_Fs, BKSGE_10_Fs

#define BKSGE_500_Fs	\
	BKSGE_100_Fs, BKSGE_100_Fs, BKSGE_100_Fs, BKSGE_100_Fs, BKSGE_100_Fs

GTEST_TEST(TppTest, AnyOfTest)
{
	{
		BKSGE_CONSTEXPR bool t = true;
		BKSGE_CONSTEXPR bool f = false;

		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of());
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of(f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, t));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of(f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, t, t));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, t, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, f, t));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, t, t));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, t, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of(f, f, f));

		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, t, t, t, t, t, t, t, t, t));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(t, f, f, f, f, f, f, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, t, f, f, f, f, f, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, t, f, f, f, f, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, t, f, f, f, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, f, t, f, f, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, f, f, t, f, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, f, f, f, t, f, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, f, f, f, f, t, f, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, f, f, f, f, f, t, f));
		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(f, f, f, f, f, f, f, f, f, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of(f, f, f, f, f, f, f, f, f, f));

		BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(BKSGE_100_Fs, t));
		BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of(BKSGE_100_Fs, f));

		//BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::tpp::any_of(BKSGE_500_Fs, t));
		//BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::tpp::any_of(BKSGE_500_Fs, f));
	}
}

#undef BKSGE_10_Fs
#undef BKSGE_100_Fs
#undef BKSGE_500_Fs
