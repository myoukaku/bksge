﻿/**
 *	@file	unit_test_fnd_unordered_multimap_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/unordered_map.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_unordered_multimap_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct is_key_1
{
	template <typename T>
	bool operator()(T const& x) const
	{
		return x.first == 1;
	}
};

inline /*BKSGE_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		bksge::unordered_multimap<int, char> m =
		{
			{3, 'a'},
			{1, 'b'},
			{4, 'c'},
		};
		auto r = bksge::erase_if(m, is_key_1{});
		VERIFY(r == 1);
		bksge::unordered_multimap<int, char> const m2 =
		{
			{3, 'a'},
			{4, 'c'},
		};
		VERIFY(bksge::ranges::equal(m, m2));
	}
	return true;
}

GTEST_TEST(UnorderedMultiMapTest, EraseIfTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace bksge_unordered_multimap_test
