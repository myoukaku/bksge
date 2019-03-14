/**
 *	@file	unit_test_utility_make_index_sequence.cpp
 *
 *	@brief	make_index_sequence のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/utility/make_index_sequence.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace make_index_sequence_test
{

void MakeIndexSequenceTestSub(void)
{
}

void MakeIndexSequenceTestSub(std::size_t a)
{
	EXPECT_EQ(0u, a);
}

void MakeIndexSequenceTestSub(
	std::size_t a,
	std::size_t b,
	std::size_t c,
	std::size_t d,
	std::size_t e,
	std::size_t f,
	std::size_t g,
	std::size_t h,
	std::size_t i,
	std::size_t j)
{
	EXPECT_EQ(0u, a);
	EXPECT_EQ(1u, b);
	EXPECT_EQ(2u, c);
	EXPECT_EQ(3u, d);
	EXPECT_EQ(4u, e);
	EXPECT_EQ(5u, f);
	EXPECT_EQ(6u, g);
	EXPECT_EQ(7u, h);
	EXPECT_EQ(8u, i);
	EXPECT_EQ(9u, j);
}

template <std::size_t ... Seq>
void MakeIndexSequenceTest(bksge::index_sequence<Seq ...>)
{
	MakeIndexSequenceTestSub(Seq...);
}

GTEST_TEST(UtilityTest, MakeIndexSequenceTest)
{
	{
		using seq = bksge::make_index_sequence<0>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 0);
		MakeIndexSequenceTest(seq());
	}
	{
		using seq = bksge::make_index_sequence<1>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 1);
		MakeIndexSequenceTest(seq());
	}
	{
		using seq = bksge::make_index_sequence<10>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 10);
		MakeIndexSequenceTest(seq());
	}
	{
		using seq = bksge::make_index_sequence<100>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 100);
	}
}

}	// namespace make_index_sequence_test

}	// namespace bksge_utility_test
