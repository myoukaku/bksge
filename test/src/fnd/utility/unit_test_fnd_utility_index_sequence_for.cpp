/**
 *	@file	unit_test_fnd_utility_index_sequence_for.cpp
 *
 *	@brief	index_sequence_for のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/index_sequence_for.hpp>
#include <cstddef>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace index_sequence_for_test
{

template <std::size_t N, typename... Types>
void IndexSequenceForTest(Types...)
{
	using seq = bksge::index_sequence_for<Types...>;
	BKSGE_CONSTEXPR_EXPECT_EQ(N, seq().size());
}

GTEST_TEST(UtilityTest, IndexSequenceForTest)
{
	IndexSequenceForTest<0>();
	IndexSequenceForTest<1>(1);
	IndexSequenceForTest<1>(0.5f);
	IndexSequenceForTest<1>("hoge");
	IndexSequenceForTest<2>(1, 2);
	IndexSequenceForTest<2>(1.5, "foo");
	IndexSequenceForTest<3>(2.5, "foo", 3);
	IndexSequenceForTest<3>(5, 4, 3);
	IndexSequenceForTest<3>('a', 'b', 'c');
	IndexSequenceForTest<4>(0, 'a', "hoge", 3.5f);
	IndexSequenceForTest<5>("", 0, 0.0, 0.0f, 0);
}

}	// namespace index_sequence_for_test

}	// namespace bksge_utility_test
