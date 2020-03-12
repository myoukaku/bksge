/**
 *	@file	unit_test_fnd_algorithm_min.cpp
 *
 *	@brief	min のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace min_test
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

	EXPECT_EQ((T)3, bksge::min({(T)3}));
	EXPECT_EQ((T)1, bksge::min({(T)3, (T)1}));
	EXPECT_EQ((T)1, bksge::min({(T)3, (T)1, (T)4}));
	EXPECT_EQ((T)1, bksge::min({(T)3, (T)1, (T)4, (T)1}));
	EXPECT_EQ((T)1, bksge::min({(T)3, (T)1, (T)4, (T)1, (T)5}));
	EXPECT_EQ((T)1, bksge::min({(T)3, (T)1, (T)4, (T)1, (T)5}, bksge::less<>()));
	EXPECT_EQ((T)5, bksge::min({(T)3, (T)1, (T)4, (T)1, (T)5}, bksge::greater<>()));
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

	EXPECT_EQ((T)-3, bksge::min({(T)-3}));
	EXPECT_EQ((T)-3, bksge::min({(T)-3, (T)-1}));
	EXPECT_EQ((T)-4, bksge::min({(T)-3, (T)-1, (T)-4}));
	EXPECT_EQ((T)-4, bksge::min({(T)-3, (T)-1, (T)-4, (T)-1}));
	EXPECT_EQ((T)-5, bksge::min({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}));
	EXPECT_EQ((T)-5, bksge::min({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, bksge::less<>()));
	EXPECT_EQ((T)-1, bksge::min({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, bksge::greater<>()));
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

	EXPECT_EQ((T)-3.5, bksge::min({(T)-3.5}));
	EXPECT_EQ((T)-3.5, bksge::min({(T)-3.5, (T)1.5}));
	EXPECT_EQ((T)-4.5, bksge::min({(T)-3.5, (T)1.5, (T)-4.5}));
	EXPECT_EQ((T)-4.5, bksge::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5}));
	EXPECT_EQ((T)-5.5, bksge::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5, (T)-5.5}));
	EXPECT_EQ((T)-5.5, bksge::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5, (T)-5.5}, bksge::less<>()));
	EXPECT_EQ((T) 1.5, bksge::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5, (T)-5.5}, bksge::greater<>()));
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

	EXPECT_EQ('a', bksge::min({'a'}));
	EXPECT_EQ('x', bksge::min({'x', 'y'}));
	EXPECT_EQ('a', bksge::min({'c', 'b', 'a'}));
	EXPECT_EQ("foo", bksge::min(std::string("foo"), std::string("hoge")));
	EXPECT_EQ("ABC", bksge::min({std::string("abc"), std::string("ABC"), std::string("zzzz")}));
}

}	// namespace min_test

}	// namespace bksge_algorithm_test
