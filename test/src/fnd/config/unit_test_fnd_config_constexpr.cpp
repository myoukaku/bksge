/**
 *	@file	unit_test_fnd_config_constexpr.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_config_constexpr_test
{

BKSGE_CONSTEXPR int func1(int x)
{
	return x * 2;
}

BKSGE_CXX14_CONSTEXPR int func2(int x)
{
	x = x * 3;
	return x;
}

GTEST_TEST(ConfigTest, ConstexprTest)
{
	BKSGE_CONSTEXPR					int a = 1;
	BKSGE_CONSTEXPR_OR_CONST		int b = 2;
	BKSGE_STATIC_CONSTEXPR			int c = 3;
	BKSGE_CONSTEXPR_OR_CONST		int d = func1(4);
	BKSGE_CXX14_CONSTEXPR			int e = 5;
	BKSGE_CXX14_CONSTEXPR_OR_CONST	int f = func2(6);
	BKSGE_CXX14_STATIC_CONSTEXPR	int g = func2(7);

	EXPECT_EQ(1, a);
	EXPECT_EQ(2, b);
	EXPECT_EQ(3, c);
	EXPECT_EQ(8, d);
	EXPECT_EQ(5, e);
	EXPECT_EQ(18, f);
	EXPECT_EQ(21, g);

	static_assert(b == 2, "");
	static_assert(c == 3, "");

	char arr2[b];
	char arr3[c];
	(void)arr2;
	(void)arr3;

	static_assert(sizeof(arr2) == 2, "");
	static_assert(sizeof(arr3) == 3, "");

#if defined(BKSGE_HAS_CXX11_CONSTEXPR)
	static_assert(a == 1, "");
	static_assert(d == 8, "");

	char arr1[a];
	char arr4[d];
	(void)arr1;
	(void)arr4;

	static_assert(sizeof(arr1) == 1, "");
	static_assert(sizeof(arr4) == 8, "");
#endif

#if defined(BKSGE_HAS_CXX14_CONSTEXPR)
	static_assert(e == 5, "");
	static_assert(f == 18, "");
	static_assert(g == 21, "");

	char arr5[e];
	char arr6[f];
	char arr7[g];
	(void)arr5;
	(void)arr6;
	(void)arr7;

	static_assert(sizeof(arr5) == 5, "");
	static_assert(sizeof(arr6) == 18, "");
	static_assert(sizeof(arr7) == 21, "");
#endif
}

}	// namespace bksge_config_constexpr_test
