﻿/**
 *	@file	unit_test_algorithm_min.cpp
 *
 *	@brief	min のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/algorithm/min.hpp>
#include <bksge/functional/less.hpp>
#include <bksge/functional/greater.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace bksge_algorithm_min_test
{

template <typename T>
void MinTestUnsigned(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::min((T)  0, (T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::min((T)  0, (T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::min((T)  1, (T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::min((T)  1, (T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::min((T)100, (T)100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::min((T)100, (T)101));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::min((T)101, (T)100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)101, bksge::min((T)101, (T)101));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)2, bksge::min((T)2, (T)3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)2, bksge::min((T)2, (T)3, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::min((T)2, (T)3, bksge::greater<>()));
}

template <typename T>
void MinTestSigned(void)
{
	MinTestUnsigned<T>();
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::min((T)  -1, (T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -2, bksge::min((T)  -1, (T)  -2));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -2, bksge::min((T)  -2, (T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -2, bksge::min((T)  -2, (T)  -2));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::min((T)-100, (T)-100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-101, bksge::min((T)-100, (T)-101));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-101, bksge::min((T)-101, (T)-100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-101, bksge::min((T)-101, (T)-101));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-3, bksge::min((T)-2, (T)-3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-3, bksge::min((T)-2, (T)-3, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2, bksge::min((T)-2, (T)-3, bksge::greater<>()));
}

template <typename T>
void MinTestFloat(void)
{
	MinTestSigned<T>();
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.00, bksge::min((T) 0.00, (T) 0.00));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.50, bksge::min((T) 0.50, (T) 0.75));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.25, bksge::min((T) 0.50, (T) 0.25));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-0.75, bksge::min((T)-0.50, (T)-0.75));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-0.50, bksge::min((T)-0.50, (T)-0.25));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1.5, bksge::min((T) 1.5, (T) 2.5, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2.5, bksge::min((T)-1.5, (T)-2.5, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 2.5, bksge::min((T) 1.5, (T) 2.5, bksge::greater<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1.5, bksge::min((T)-1.5, (T)-2.5, bksge::greater<>()));
}

GTEST_TEST(AlgorithmTest, MinTest)
{
	MinTestUnsigned<unsigned char>();
	MinTestUnsigned<unsigned short>();
	MinTestUnsigned<unsigned int>();
	MinTestUnsigned<unsigned long>();
	MinTestUnsigned<unsigned long long>();

	MinTestSigned<signed char>();
	MinTestSigned<signed short>();
	MinTestSigned<signed int>();
	MinTestSigned<signed long>();
	MinTestSigned<signed long long>();

	MinTestFloat<float>();
	MinTestFloat<double>();
	MinTestFloat<long double>();

	EXPECT_EQ('x', bksge::min('x', 'y'));
	EXPECT_EQ("foo", bksge::min(std::string("foo"), std::string("hoge")));
}

}	// namespace bksge_algorithm_min_test
