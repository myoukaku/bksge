/**
 *	@file	unit_test_fnd_config_likely.cpp
 *
 *	@brief	BKSGE_LIKELY のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ConfigTest, LikelyTest)
{
	bool f1 = true;
	bool f2 = false;

	if (BKSGE_LIKELY(f1))
	{
		EXPECT_TRUE(f1);
	}
	else
	{
		EXPECT_FALSE(f1);
	}

	if (BKSGE_UNLIKELY(f1))
	{
		EXPECT_TRUE(f1);
	}
	else
	{
		EXPECT_FALSE(f1);
	}

	if (BKSGE_LIKELY(f2))
	{
		EXPECT_TRUE(f2);
	}
	else
	{
		EXPECT_FALSE(f2);
	}

	if (BKSGE_UNLIKELY(f2))
	{
		EXPECT_TRUE(f2);
	}
	else
	{
		EXPECT_FALSE(f2);
	}
}
