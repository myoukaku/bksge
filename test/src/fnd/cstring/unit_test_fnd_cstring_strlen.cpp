/**
 *	@file	unit_test_fnd_cstring_strlen.cpp
 *
 *	@brief	strlenのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cstring/strlen.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(CStringTest, StrLenTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 0u, bksge::strlen(""));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 3u, bksge::strlen("abc"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen("Hello World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4u, bksge::strlen("Hell\0o World"));

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 0u, bksge::strlen(L""));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 3u, bksge::strlen(L"abc"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen(L"Hello World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4u, bksge::strlen(L"Hell\0o World"));

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 0u, bksge::strlen(u8""));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 3u, bksge::strlen(u8"abc"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen(u8"Hello World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4u, bksge::strlen(u8"Hell\0o World"));
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 0u, bksge::strlen(u""));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 3u, bksge::strlen(u"abc"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen(u"Hello World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4u, bksge::strlen(u"Hell\0o World"));
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 0u, bksge::strlen(U""));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 3u, bksge::strlen(U"abc"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(11u, bksge::strlen(U"Hello World"));
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4u, bksge::strlen(U"Hell\0o World"));
#endif
}
