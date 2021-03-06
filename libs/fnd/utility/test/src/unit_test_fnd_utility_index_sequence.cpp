﻿/**
 *	@file	unit_test_fnd_utility_index_sequence.cpp
 *
 *	@brief	index_sequence のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace index_sequence_test
{

void IndexSequenceTestSub()
{
}

void IndexSequenceTestSub(bksge::size_t a)
{
	EXPECT_EQ(20u, a);
}

void IndexSequenceTestSub(
	bksge::size_t a,
	bksge::size_t b,
	bksge::size_t c,
	bksge::size_t d,
	bksge::size_t e,
	bksge::size_t f)
{
	EXPECT_EQ(1u, a);
	EXPECT_EQ(1u, b);
	EXPECT_EQ(2u, c);
	EXPECT_EQ(3u, d);
	EXPECT_EQ(5u, e);
	EXPECT_EQ(8u, f);
}

template <bksge::size_t ... Seq>
void IndexSequenceTest(bksge::index_sequence<Seq ...>)
{
	IndexSequenceTestSub(Seq...);
}

GTEST_TEST(UtilityTest, IndexSequenceTest)
{
	{
		using seq = bksge::index_sequence<>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 0);
		IndexSequenceTest(seq());
	}
	{
		using seq = bksge::index_sequence<20>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 1);
		IndexSequenceTest(seq());
	}
	{
		using seq = bksge::index_sequence<1, 1, 2, 3, 5, 8>;
		BKSGE_CONSTEXPR_EXPECT_TRUE(seq().size() == 6);
		IndexSequenceTest(seq());
	}
}

}	// namespace index_sequence_test

}	// namespace bksge_utility_test
