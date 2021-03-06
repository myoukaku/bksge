﻿/**
 *	@file	unit_test_fnd_string_to_wstring.cpp
 *
 *	@brief	to_wstring のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/string/to_wstring.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_string_test
{

namespace to_wstring_test
{

GTEST_TEST(StringTest, ToWStringTest)
{
	{
		int x1 =  0;
		int x2 = -1;
		int x3 =  1;
		int x4 =  123456789;
		int x5 = -123456789;
		EXPECT_EQ(L"0",          bksge::to_wstring(x1));
		EXPECT_EQ(L"-1",         bksge::to_wstring(x2));
		EXPECT_EQ(L"1",          bksge::to_wstring(x3));
		EXPECT_EQ(L"123456789",  bksge::to_wstring(x4));
		EXPECT_EQ(L"-123456789", bksge::to_wstring(x5));
	}
	{
		long x1 =  0;
		long x2 = -1;
		long x3 =  1;
		long x4 =  123456789;
		long x5 = -123456789;
		EXPECT_EQ(L"0",          bksge::to_wstring(x1));
		EXPECT_EQ(L"-1",         bksge::to_wstring(x2));
		EXPECT_EQ(L"1",          bksge::to_wstring(x3));
		EXPECT_EQ(L"123456789",  bksge::to_wstring(x4));
		EXPECT_EQ(L"-123456789", bksge::to_wstring(x5));
	}
	{
		long long x1 =  0;
		long long x2 = -1;
		long long x3 =  1;
		long long x4 =  123456789;
		long long x5 = -123456789;
		EXPECT_EQ(L"0",          bksge::to_wstring(x1));
		EXPECT_EQ(L"-1",         bksge::to_wstring(x2));
		EXPECT_EQ(L"1",          bksge::to_wstring(x3));
		EXPECT_EQ(L"123456789",  bksge::to_wstring(x4));
		EXPECT_EQ(L"-123456789", bksge::to_wstring(x5));
	}
	{
		unsigned int x1 =  0;
		unsigned int x2 =  1;
		unsigned int x3 =  2;
		unsigned int x4 =  123456789;
		unsigned int x5 = 1234567890;
		EXPECT_EQ(L"0",          bksge::to_wstring(x1));
		EXPECT_EQ(L"1",          bksge::to_wstring(x2));
		EXPECT_EQ(L"2",          bksge::to_wstring(x3));
		EXPECT_EQ(L"123456789",  bksge::to_wstring(x4));
		EXPECT_EQ(L"1234567890", bksge::to_wstring(x5));
	}
	{
		unsigned long x1 =  0;
		unsigned long x2 =  1;
		unsigned long x3 =  2;
		unsigned long x4 =  123456789;
		unsigned long x5 = 1234567890;
		EXPECT_EQ(L"0",          bksge::to_wstring(x1));
		EXPECT_EQ(L"1",          bksge::to_wstring(x2));
		EXPECT_EQ(L"2",          bksge::to_wstring(x3));
		EXPECT_EQ(L"123456789",  bksge::to_wstring(x4));
		EXPECT_EQ(L"1234567890", bksge::to_wstring(x5));
	}
	{
		unsigned long long x1 =  0;
		unsigned long long x2 =  1;
		unsigned long long x3 =  2;
		unsigned long long x4 =  123456789;
		unsigned long long x5 = 1234567890;
		EXPECT_EQ(L"0",          bksge::to_wstring(x1));
		EXPECT_EQ(L"1",          bksge::to_wstring(x2));
		EXPECT_EQ(L"2",          bksge::to_wstring(x3));
		EXPECT_EQ(L"123456789",  bksge::to_wstring(x4));
		EXPECT_EQ(L"1234567890", bksge::to_wstring(x5));
	}
	{
		float x1 =  0.0f;
		float x2 =  1.0f;
		float x3 = -0.5f;
		float x4 =  0.000001f;
		float x5 = 1234567890.0f;
		EXPECT_EQ(L"0.000000",          bksge::to_wstring(x1));
		EXPECT_EQ(L"1.000000",          bksge::to_wstring(x2));
		EXPECT_EQ(L"-0.500000",         bksge::to_wstring(x3));
		EXPECT_EQ(L"0.000001",          bksge::to_wstring(x4));
		EXPECT_EQ(L"1234567936.000000", bksge::to_wstring(x5));
	}
	{
		double x1 =  0.0;
		double x2 =  1.0;
		double x3 = -0.5;
		double x4 =  0.000001;
		double x5 = 1234567890.0;
		EXPECT_EQ(L"0.000000",          bksge::to_wstring(x1));
		EXPECT_EQ(L"1.000000",          bksge::to_wstring(x2));
		EXPECT_EQ(L"-0.500000",         bksge::to_wstring(x3));
		EXPECT_EQ(L"0.000001",          bksge::to_wstring(x4));
		EXPECT_EQ(L"1234567890.000000", bksge::to_wstring(x5));
	}
	{
		long double x1 =  0.0L;
		long double x2 =  1.0L;
		long double x3 = -0.5L;
		long double x4 =  0.000001L;
		long double x5 = 1234567890.0L;
		EXPECT_EQ(L"0.000000",          bksge::to_wstring(x1));
		EXPECT_EQ(L"1.000000",          bksge::to_wstring(x2));
		EXPECT_EQ(L"-0.500000",         bksge::to_wstring(x3));
		EXPECT_EQ(L"0.000001",          bksge::to_wstring(x4));
		EXPECT_EQ(L"1234567890.000000", bksge::to_wstring(x5));
	}
}

}	// namespace to_wstring_test

}	// namespace bksge_string_test
