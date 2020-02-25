/**
 *	@file	unit_test_fnd_optional_hash.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(OptionalTest, HashTest)
{
	{
		const bksge::optional<int> o;
		EXPECT_EQ(0u, std::hash<bksge::optional<int>>()(o));
	}
	{
		const bksge::optional<int> o(1);
		EXPECT_EQ(
			std::hash<int>()(1),
			std::hash<bksge::optional<int>>()(o));
	}
	{
		const bksge::optional<int> o(42);
		EXPECT_EQ(
			std::hash<int>()(42),
			std::hash<bksge::optional<int>>()(o));
	}
}
