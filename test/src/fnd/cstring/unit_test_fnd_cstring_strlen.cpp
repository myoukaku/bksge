/**
 *	@file	unit_test_fnd_cstring_strlen.cpp
 *
 *	@brief	strlenのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstring/strlen.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(CStringTest, StrLenTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0u, bksge::strlen(""));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0u, bksge::strlen(L""));

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3u, bksge::strlen("abc"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3u, bksge::strlen(L"abc"));

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen("Hello World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen(L"Hello World"));

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4u, bksge::strlen("Hell\0o World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4u, bksge::strlen(L"Hell\0o World"));
}
