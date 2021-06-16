/**
 *	@file	unit_test_fnd_unordered_set_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/unordered_set.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_unordered_set_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*BKSGE_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		bksge::unordered_set<int> v = {3,1,4,5,2};
		auto r = bksge::erase_if(v, [](int x) { return x % 2 == 0; });
		VERIFY(r == 2);
		bksge::unordered_set<int> v2 = {3,1,5};
		VERIFY(v == v2);
	}
	{
		bksge::unordered_set<int> v = {3,1,4,5,9,2,6,};
		auto r = bksge::erase_if(v, [](int x) { return x >= 5; });
		VERIFY(r == 3);
		bksge::unordered_set<int> v2 = {3,1,4,2,};
		VERIFY(v == v2);
	}
	return true;
}

GTEST_TEST(UnorderedSetTest, EraseIfTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace bksge_unordered_set_test
