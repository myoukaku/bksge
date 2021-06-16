/**
 *	@file	unit_test_fnd_set_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/set.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_set_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*BKSGE_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		bksge::set<int> v = {3,1,4,5,2};
		auto r = bksge::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		const int v2[] = {1,3,5,};
		VERIFY(bksge::ranges::equal(v, v2));
	}
	{
		bksge::set<int> v = {3,1,4,5,9,2,6,};
		auto r = bksge::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 3);
		const int v2[] = {1,2,3,4,};
		VERIFY(bksge::ranges::equal(v, v2));
	}
	return true;
}

GTEST_TEST(SetTest, EraseIfTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace bksge_set_test
