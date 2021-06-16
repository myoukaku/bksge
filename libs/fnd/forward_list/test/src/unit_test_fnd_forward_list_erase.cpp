/**
 *	@file	unit_test_fnd_forward_list_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_forward_list_test
{

namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline /*BKSGE_CXX14_CONSTEXPR*/ bool
EraseTest()
{
	{
		bksge::forward_list<int> v = {3,1,4,5,2};
		auto r = bksge::erase(v, 1);
		VERIFY(r == 1);
		const int v2[] = {3,4,5,2,};
		VERIFY(bksge::ranges::equal(v, v2));
	}
	{
		bksge::forward_list<int> v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9,};
		auto r = bksge::erase(v, 9);
		VERIFY(r == 10);
		const int v2[] = {1,2,3,4,5};
		VERIFY(bksge::ranges::equal(v, v2));
	}
	return true;
}

GTEST_TEST(ForwardListTest, EraseTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseTest());
}

#undef VERIFY

}	// namespace erase_test

}	// namespace bksge_forward_list_test
