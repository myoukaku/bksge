/**
 *	@file	unit_test_fnd_utility_make_index_sequence.cpp
 *
 *	@brief	make_index_sequence のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace make_index_sequence_test
{

void MakeIndexSequenceTestSub(void)
{
}

void MakeIndexSequenceTestSub(bksge::size_t a)
{
	EXPECT_EQ(0u, a);
}

void MakeIndexSequenceTestSub(
	bksge::size_t a,
	bksge::size_t b,
	bksge::size_t c,
	bksge::size_t d,
	bksge::size_t e,
	bksge::size_t f,
	bksge::size_t g,
	bksge::size_t h,
	bksge::size_t i,
	bksge::size_t j)
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

template <bksge::size_t ... Seq>
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
