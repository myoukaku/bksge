/**
 *	@file	unit_test_functional_hash_combine.cpp
 *
 *	@brief	hash_combine のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/functional/hash_combine.hpp>
#include <gtest/gtest.h>
#include <string>

GTEST_TEST(FunctionalTest, HashCombineTest)
{
	auto const h0 = bksge::hash_combine(0);
	auto const h1 = bksge::hash_combine(0.5f);
	auto const h2 = bksge::hash_combine(true);
	auto const h3 = bksge::hash_combine(std::string(""));
	auto const h4 = bksge::hash_combine(std::string("a"));
	auto const h5 = bksge::hash_combine(1, 0.25);
	auto const h6 = bksge::hash_combine(0.25, 1);
	auto const h7 = bksge::hash_combine(1, 2, 3);
	auto const h8 = bksge::hash_combine(3, 1, 2);
	auto const h9 = bksge::hash_combine(1, 3, 2);
	auto const h10 = bksge::hash_combine(false, 42, std::string("abc"));
	auto const h11 = bksge::hash_combine(false, 42, std::string("abc"), 0.5);

	EXPECT_TRUE(h0 != h1);
	EXPECT_TRUE(h0 != h2);
	EXPECT_TRUE(h0 != h3);
	EXPECT_TRUE(h0 != h4);
	EXPECT_TRUE(h0 != h5);
	EXPECT_TRUE(h0 != h6);
	EXPECT_TRUE(h0 != h7);
	EXPECT_TRUE(h0 != h8);
	EXPECT_TRUE(h0 != h9);
	EXPECT_TRUE(h0 != h10);
	EXPECT_TRUE(h0 != h11);

	EXPECT_TRUE(h1 != h2);
	EXPECT_TRUE(h1 != h3);
	EXPECT_TRUE(h1 != h4);
	EXPECT_TRUE(h1 != h5);
	EXPECT_TRUE(h1 != h6);
	EXPECT_TRUE(h1 != h7);
	EXPECT_TRUE(h1 != h8);
	EXPECT_TRUE(h1 != h9);
	EXPECT_TRUE(h1 != h10);
	EXPECT_TRUE(h1 != h11);

	EXPECT_TRUE(h2 != h3);
	EXPECT_TRUE(h2 != h4);
	EXPECT_TRUE(h2 != h5);
	EXPECT_TRUE(h2 != h6);
	EXPECT_TRUE(h2 != h7);
	EXPECT_TRUE(h2 != h8);
	EXPECT_TRUE(h2 != h9);
	EXPECT_TRUE(h2 != h10);
	EXPECT_TRUE(h2 != h11);

	EXPECT_TRUE(h3 != h4);
	EXPECT_TRUE(h3 != h5);
	EXPECT_TRUE(h3 != h6);
	EXPECT_TRUE(h3 != h7);
	EXPECT_TRUE(h3 != h8);
	EXPECT_TRUE(h3 != h9);
	EXPECT_TRUE(h3 != h10);
	EXPECT_TRUE(h3 != h11);

	EXPECT_TRUE(h4 != h5);
	EXPECT_TRUE(h4 != h6);
	EXPECT_TRUE(h4 != h7);
	EXPECT_TRUE(h4 != h8);
	EXPECT_TRUE(h4 != h9);
	EXPECT_TRUE(h4 != h10);
	EXPECT_TRUE(h4 != h11);

	EXPECT_TRUE(h5 != h6);
	EXPECT_TRUE(h5 != h7);
	EXPECT_TRUE(h5 != h8);
	EXPECT_TRUE(h5 != h9);
	EXPECT_TRUE(h5 != h10);
	EXPECT_TRUE(h5 != h11);

	EXPECT_TRUE(h6 != h7);
	EXPECT_TRUE(h6 != h8);
	EXPECT_TRUE(h6 != h9);
	EXPECT_TRUE(h6 != h10);
	EXPECT_TRUE(h6 != h11);

	EXPECT_TRUE(h7 != h8);
	EXPECT_TRUE(h7 != h9);
	EXPECT_TRUE(h7 != h10);
	EXPECT_TRUE(h7 != h11);

	EXPECT_TRUE(h8 != h9);
	EXPECT_TRUE(h8 != h10);
	EXPECT_TRUE(h8 != h11);

	EXPECT_TRUE(h9 != h10);
	EXPECT_TRUE(h9 != h11);

	EXPECT_TRUE(h10 != h11);

	auto const h0_2 = bksge::hash_combine(0);
	auto const h1_2 = bksge::hash_combine(0.5f);
	auto const h2_2 = bksge::hash_combine(true);
	auto const h3_2 = bksge::hash_combine(std::string(""));
	auto const h4_2 = bksge::hash_combine(std::string("a"));
	auto const h5_2 = bksge::hash_combine(1, 0.25);
	auto const h6_2 = bksge::hash_combine(0.25, 1);
	auto const h7_2 = bksge::hash_combine(1, 2, 3);
	auto const h8_2 = bksge::hash_combine(3, 1, 2);
	auto const h9_2 = bksge::hash_combine(1, 3, 2);
	auto const h10_2 = bksge::hash_combine(false, 42, std::string("abc"));
	auto const h11_2 = bksge::hash_combine(false, 42, std::string("abc"), 0.5);

	EXPECT_TRUE(h0  == h0_2);
	EXPECT_TRUE(h1  == h1_2);
	EXPECT_TRUE(h2  == h2_2);
	EXPECT_TRUE(h3  == h3_2);
	EXPECT_TRUE(h4  == h4_2);
	EXPECT_TRUE(h5  == h5_2);
	EXPECT_TRUE(h6  == h6_2);
	EXPECT_TRUE(h7  == h7_2);
	EXPECT_TRUE(h8  == h8_2);
	EXPECT_TRUE(h9  == h9_2);
	EXPECT_TRUE(h10 == h10_2);
	EXPECT_TRUE(h11 == h11_2);
}
