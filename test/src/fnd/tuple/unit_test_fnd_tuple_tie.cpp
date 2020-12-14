/**
 *	@file	unit_test_fnd_tuple_tie.cpp
 *
 *	@brief	tie のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/tie.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tie_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		int x1 = 0;
		int x2 = 0;
		int y1 = 0;
		int y2 = 0;
		bksge::tuple<int, int> ta(1, 1);
		bksge::tuple<const int&, const int&> tc(x1, x2);

		bksge::tie(y1, y2) = ta;
		VERIFY(y1 == 1 && y2 == 1);

		bksge::tie(y1, y2) = tc;
		VERIFY(y1 == 0 && y2 == 0);
	}
	{
		int i {};
		float f {};

		bksge::tie(i, bksge::ignore, f) = bksge::make_tuple(42, 3.14, 0.5f);
		VERIFY(i == 42);
		VERIFY(f == 0.5f);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, TieTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace tie_test

}	// namespace bksge_tuple_test
